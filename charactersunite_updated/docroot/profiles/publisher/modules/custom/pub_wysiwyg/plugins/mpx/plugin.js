/*
 * CKEditor custom <mpx> element plugin
 *
 * This is loaded from the pub_wysiwyg module.
 *
 * @author breathingrock
 */
(function() {
  // Modify the CKEDITOR.dtd in order for it to allow our mpx tags.
  CKEDITOR.dtd.mpx = {};
  // Designate the mpx element as $block or $inline.
  CKEDITOR.dtd.$block.mpx = 1;
  // Allow <mpx> to be inside a <p> or <div> tag.
  CKEDITOR.dtd.p.mpx = 1;
  CKEDITOR.dtd.div.mpx = 1;
  // MPX plugin definition.
  CKEDITOR.plugins.add('mpx', {
    lang: ['en', 'pt', 'ja', 'hu', 'it', 'fr', 'tr', 'ru', 'de', 'ar', 'nl', 'pl', 'vi'],
    init: function(editor) {
      editor.config.contentsCss.mpx = this.path + 'css/styles.css';
      editor.addContentsCss(this.path + 'css/styles.css');

      editor.addCommand('mpx', new CKEDITOR.dialogCommand('mpx', {
        allowedContent: 'mpx[!src,!height,!width,class]'
      }));

      editor.ui.addButton('MPX', {
        label: editor.lang.mpx.button,
        toolbar: 'insert',
        command: 'mpx',
        icon: this.path + 'images/icon.png'
      });

      if (editor.contextMenu) {
        editor.addMenuGroup('mpxGroup');
        editor.addMenuItem('MPX', {
            label: 'Edit MPX Video',
            icon: this.path + 'images/icon.png',
            command: 'mpx',
            group: 'mpxGroup'
        });
        editor.contextMenu.addListener(function(element) {
          if (element.getAscendant('mpx', true)) {
            return { MPX: CKEDITOR.TRISTATE_OFF };
          }
        });
      }

      CKEDITOR.dialog.add('mpx', function (instance) {
        var video;

        return {
          title: editor.lang.mpx.title,
          minWidth: 500,
          minHeight: 100,
          contents: [{
            id: 'mpxPlugin',
            expand: true,
            elements: [{
              type: 'hbox',
              widths: [ '70%', '15%', '15%' ],
              children: [{
                id: 'txtUrl',
                type: 'text',
                label: editor.lang.mpx.txtUrl,
                validate: function() {
                  if (this.isEnabled()) {
                    url = this.getValue();
                    if (!url || url.length === 0) {
                      alert(editor.lang.mpx.noUrl);
                      return false;
                    }
                    if (!url.match(/^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$/)) {
                      alert(editor.lang.mpx.invalidUrl);
                      return false;
                    }
                  }
                },
                setup: function (element) {
                  this.setValue(element.getAttribute('url'));
                },
                commit: function (element) {
                  element.setAttribute('class', 'mpx-video');
                  element.setAttribute('url', this.getValue());
                }
              },
              {
                id: 'txtWidth',
                type: 'text',
                width: '60px',
                label: editor.lang.mpx.txtWidth,
                'default': editor.config.mpx_width != null ? editor.config.mpx_width : '640',
                validate: function() {
                  if (this.getValue()) {
                    var width = parseInt(this.getValue()) || 0;
                    if (width === 0) {
                      alert(editor.lang.mpx.invalidWidth);
                      return false;
                    }
                  }
                  else {
                    alert(editor.lang.mpx.noWidth);
                    return false;
                  }
                },
                setup: function (element) {
                  this.setValue(element.getAttribute('width'));
                },
                commit: function (element) {
                  element.setAttribute('width', this.getValue());
                }
              },
              {
                id: 'txtHeight',
                type: 'text',
                width: '60px',
                label: editor.lang.mpx.txtHeight,
                'default': editor.config.mpx_height != null ? editor.config.mpx_height : '360',
                validate: function() {
                  if (this.getValue()) {
                    var height = parseInt(this.getValue()) || 0;
                    if (height === 0) {
                      alert(editor.lang.mpx.invalidHeight);
                      return false;
                    }
                  }
                  else {
                    alert(editor.lang.mpx.noHeight);
                    return false;
                  }
                },
                setup: function (element) {
                  this.setValue(element.getAttribute('height'));
                },
                commit: function (element) {
                  element.setAttribute('height', this.getValue());
                }
              }]
            }]
          }],
          onShow: function () {
            var selection = editor.getSelection();
            var element = selection.getStartElement();
            if (element) {
              element = element.getAscendant('mpx', true);
            }
            if (!element || element.getName() != 'mpx') {
              element = editor.document.createElement('mpx');
              this.insertMode = true;
            }
            else {
              this.insertMode = false;
            }
            this.element = element; 
            if (!this.insertMode) {
              this.setupContent(this.element);
            }
          },
          onOk: function() {
            var dialog = this;
            var mpx = this.element;
            this.commitContent(mpx);
            if (this.insertMode) {
              editor.insertElement(mpx);
            }
          }
        };
      });
    }
  });
})();
