/*
 * CKEditor custom <youtube> element plugin
 *
 * This is loaded from the pub_wysiwyg module.
 *
 * @author ericduran & breathingrock
 */
(function() {
  // We need to modify the CKEDITOR.dtd in order for it to allow our custom youtube tag.
  // List of tag names it can contain inside <youtube>.
  CKEDITOR.dtd.youtube = {};
  // We need to choose $block or $inline.
  CKEDITOR.dtd.$block.youtube = 1;
  // Allow <youtube> to be inside a <p> or <div> tag.
  //CKEDITOR.dtd.body.youtube = 1;
  CKEDITOR.dtd.p.youtube = 1;
  CKEDITOR.dtd.div.youtube = 1;

  CKEDITOR.plugins.add('youtube', {
    lang: ['en', 'pt', 'ja', 'hu', 'it', 'fr', 'tr', 'ru', 'de', 'ar', 'nl', 'pl', 'vi'],
    init: function(editor) {
      editor.config.contentsCss.youtube = this.path + 'css/styles.css';
      editor.addContentsCss(this.path + 'css/styles.css');

      editor.addCommand('youtube', new CKEDITOR.dialogCommand('youtube', {
        allowedContent: 'youtube[!src,!height,!width,,rel,start,autoplay,class]'
      }));

      editor.ui.addButton('Youtube', {
        label: editor.lang.youtube.button,
        toolbar: 'insert',
        command: 'youtube',
        icon: this.path + 'images/icon.png'
      });

      if (editor.contextMenu) {
        editor.addMenuGroup('youtubeGroup');
        editor.addMenuItem('Youtube', {
          label: 'Edit Youtube Video',
          icon: this.path + 'images/icon.png',
          command: 'youtube',
          group: 'youtubeGroup'
        });
        editor.contextMenu.addListener(function(element) {
          if (element.getAscendant('youtube', true)) {
            return { Youtube: CKEDITOR.TRISTATE_OFF };
          }
        });
      }

      CKEDITOR.dialog.add('youtube', function (instance) {
        return {
          title: editor.lang.youtube.title,
          minWidth: 500,
          minHeight: 100,
          contents: [{
            id: 'youtubePlugin',
            expand: true,
            elements: [{
              type: 'hbox',
              widths: [ '70%', '15%', '15%' ],
              children: [{
                id: 'txtUrl',
                type: 'text',
                label: editor.lang.youtube.txtUrl,
                validate: function() {
                  if (this.isEnabled()) {
                    if (!this.getValue()) {
                      alert(editor.lang.youtube.noCode);
                      return false;
                    }
                    else{
                      var video = youtubeVideoId(this.getValue());
                      if ( this.getValue().length === 0 ||  video === false) {
                        alert(editor.lang.youtube.invalidUrl);
                        return false;
                      }
                    }
                  }
                },
                setup: function (element) {
                  this.setValue(element.getAttribute('src'));
                },
                commit: function (element) {
                  element.setAttribute('class', 'google-youtube');
                  element.setAttribute('src', this.getValue());
                }
              },
              {
                id: 'txtWidth',
                type: 'text',
                width: '60px',
                label: editor.lang.youtube.txtWidth,
                'default': editor.config.youtube_width != null ? editor.config.youtube_width : '640',
                validate: function() {
                  if (this.getValue()) {
                    var width = parseInt(this.getValue()) || 0;
                    if (width === 0) {
                      alert(editor.lang.youtube.invalidWidth);
                      return false;
                    }
                  }
                  else {
                    alert(editor.lang.youtube.noWidth);
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
                type: 'text',
                id: 'txtHeight',
                width: '60px',
                label: editor.lang.youtube.txtHeight,
                'default': editor.config.youtube_height != null ? editor.config.youtube_height : '360',
                validate: function() {
                  if (this.getValue()) {
                    var height = parseInt(this.getValue()) || 0;

                    if (height === 0) {
                      alert(editor.lang.youtube.invalidHeight);
                      return false;
                    }
                  }
                  else {
                    alert(editor.lang.youtube.noHeight);
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
              element = element.getAscendant('youtube', true);
            }
            if (!element || element.getName() != 'youtube') {
              element = editor.document.createElement('youtube');
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
            var youtube = this.element;
            this.commitContent(youtube);
            if (this.insertMode) {
              editor.insertElement(youtube);
            }
          }
        };
      });
    }
  });

  /**
   * JavaScript function to match (and return) the video Id
   * of any valid Youtube Url, given as input string.
   * @author: Stephan Schmitz <eyecatchup@gmail.com>
   * @url: http://stackoverflow.com/a/10315969/624466
   */
  function youtubeVideoId(url) {
    var p = /^(?:https?:\/\/)?(?:www\.)?(?:youtu\.be\/|youtube\.com\/(?:embed\/|v\/|watch\?v=|watch\?.+&v=))((\w|-){11})(?:\S+)?$/;
    return ( url.match( p ) ) ? RegExp.$1 : false;
  }
})();
