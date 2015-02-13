// $Id$

/**
 * @file
 * Written by Henri MEDOT <henri.medot[AT]absyx[DOT]fr>
 * http://www.absyx.fr
 *
 * Released under the GPLv2 license.
 */

(function($){

  // Rectangle class.
  var Rectangle = function(x, y, width, height) {
    x = x || 0;
    if (x.length) {
      y = x[1];
      width = x[2];
      height = x[3];
      x = x[0];
    }
    this.x = x || 0;
    this.y = y || 0;
    this.width = width || 0;
    this.height = height || 0;
  };

  $.extend(Rectangle, {
    MAP: [9, 8, 12, 4, 6, 2, 3, 1],
    T: 8, R: 4, B: 2, L: 1
  });

  $.extend(Rectangle.prototype, {

    top: function(top) {
      if (top !== undefined) {
        this.height -= top - this.y;
        this.y = top;
        return this;
      }
      return this.y;
    },

    right: function(right) {
      if (right !== undefined) {
        this.width = right - this.x;
        return this;
      }
      return this.x + this.width;
    },

    bottom: function(bottom) {
      if (bottom !== undefined) {
        this.height = bottom - this.y;
        return this;
      }
      return this.y + this.height;
    },

    left: function(left) {
      if (left !== undefined) {
        this.width -= left - this.x;
        this.x = left;
        return this;
      }
      return this.x;
    },

    location: function(x, y) {
      if (x !== undefined) {
        if (x.length) {
          y = x[1];
          x = x[0];
        }
        this.x = x;
        this.y = y;
        return this;
      }
      return [this.x, this.y];
    },

    size: function(width, height) {
      if (width !== undefined) {
        if (width.length) {
          height = width[1];
          width = width[0];
        }
        this.width = width;
        this.height = height;
        return this;
      }
      return [this.width, this.height];
    },

    scale: function(xscale, yscale) {
      if (xscale.length) {
        yscale = xscale[1];
        xscale = xscale[0];
      }
      this.x *= xscale;
      this.y *= yscale;
      this.width *= xscale;
      this.height *= yscale;
      return this;
    },

    intersection: function(rect) {
      this.left(Math.max(this.x, rect.x));
      this.top(Math.max(this.y, rect.y));
      this.right(Math.min(this.right(), rect.right()));
      this.bottom(Math.min(this.bottom(), rect.bottom()));
      return this;
    },

    union: function(rect) {
      this.left(Math.min(this.x, rect.x));
      this.top(Math.min(this.y, rect.y));
      this.right(Math.max(this.right(), rect.right()));
      this.bottom(Math.max(this.bottom(), rect.bottom()));
      return this;
    },

    equals: function(rect) {
      return (this.x == rect.x) && (this.y == rect.y) && (this.width == rect.width) && (this.height == rect.height);
    },

    contains: function(rect) {
      return this.union(rect).equals(this);
    },

    setRect: function(rect) {
      this.x = rect.x;
      this.y = rect.y;
      this.width = rect.width;
      this.height = rect.height;
      return this;
    },

    clone: function() {
      return new Rectangle(this.x, this.y, this.width, this.height);
    },

    toArray: function() {
      return [this.x, this.y, this.width, this.height];
    },

    round: function() {
      this.x = Math.round(this.x);
      this.y = Math.round(this.y);
      this.width = Math.round(this.width);
      this.height = Math.round(this.height);
      return this;
    },

    isEmpty: function() {
      return (this.width <= 0) || (this.height <= 0);
    },

    ifEmpty: function(rect) {
      return (this.isEmpty()) ? this.setRect(rect) : this;
    },

    applyTo: function($obj) {
      $obj.css({
        'left': this.x,
        'top': this.y
      }).width(this.width).height(this.height);
      return this;
    },

    ratio: function(ratio, anchor) {
      var w, h, m = Rectangle.MAP[anchor || 0];
      if (ratio > 1) {
        w = this.width;
        h = w / ratio;
      }
      else {
        h = this.height;
        w = h * ratio;
      }
      if (m & Rectangle.R) {
        this.x = this.right() - w;
      }
      if (m & Rectangle.B) {
        this.y = this.bottom() - h;
      }
      this.width = w;
      this.height = h;
      return this;
    },

    constraint: function(c) {
      if (c.moveOnly) {
        if (c.minRect) {
          this.location(Math.min(this.x, c.minRect.x), Math.min(this.y, c.minRect.y))
            .location(Math.max(this.right(), c.minRect.right()) - this.width, Math.max(this.bottom(), c.minRect.bottom()) - this.height);
        }
        if (c.maxRect) {
          this.location(Math.max(this.x, c.maxRect.x), Math.max(this.y, c.maxRect.y))
            .location(Math.min(this.right(), c.maxRect.right()) - this.width, Math.min(this.bottom(), c.maxRect.bottom()) - this.height);
        }
      }
      else {
        var anchor = c.anchor || 0,
          m = Rectangle.MAP[anchor];

        if (c.minRect) {
          this.union(c.minRect);
        }
        else if (c.minSize) {
          var w = Math.max(this.width, c.minSize[0]);
          if (m & Rectangle.R) {
            this.left(this.right() - w);
          }
          else {
            this.width = w;
          }

          var h = Math.max(this.height, c.minSize[1]);
          if (m & Rectangle.B) {
            this.top(this.bottom() - h);
          }
          else {
            this.height = h;
          }
        }

        if (c.maxRect) {
          this.intersection(c.maxRect);
        }

        if (c.maxSize) {
          this.size(Math.min(this.width, c.maxSize[0]), Math.min(this.height, c.maxSize[1]));
        }

        if (c.ratio) {
          this.ratio(c.ratio, anchor);
        } // TODO: when ratio applied to 1x1, result might be smaller than minSize
      }

      return this;
    }

  });
  //~Rectangle class.



  // Statics.
  var R = Rectangle, $doc, $html;
  //~Statics.



  // Helper functions.
  var div = function() {
    return $('<div></div>');
  };

  var stop = function(e) {
    e.stopPropagation();
    e.preventDefault();
    return false;
  };

  var point = function(e, parent, center) {
    var offset = parent.offset();
    if (center) {
      offset.left += parent.width() / 2;
      offset.top += parent.height() / 2;
    }
    return [e.pageX - offset.left, e.pageY - offset.top];
  };

  var box = function(suffix, parent) {
    var box = div().addClass('imgfocus-box imgfocus-' + suffix).appendTo(parent).hide();
    for (var i = 0; i < 4; i++) {
      div().addClass('imgfocus-border imgfocus-border-' + i).appendTo(box);
    }
    return box;
  };

  var cursor = function(ref) {
    if (ref) {
      $html.css('cursor', ref.css('cursor')).addClass('imgfocus-cursor');
    }
    else {
      $html.css('cursor', 'auto').removeClass('imgfocus-cursor');
    }
  };
  //~Helper functions.



  // Data methods.
  var _methods = {

    point: function(e) {
      return point(e, this.wrapper);
    },

    unbindAll: function() {
      this.targets.unbind('.imgfocus');
      return this;
    },

    setIdle: function() {
      var data = this.unbindAll();
      data.oldSelRect = (data.selRect) ? data.selRect.clone() : null;
      cursor();

      data.wrapper.bind('mousedown.imgfocus', function(e) {
        var p = data.point(e);
        data.selRect = new R(p[0], p[1], 1, 1).constraint(data.constraints());
        data.repaint().setResize(4, [0, 0]);
        return stop(e);
      });

      $.each(data.handles, function(i) {
        (function (data, handle, i) {
          handle.bind('mousedown.imgfocus', function(e) {
            var p = point(e, handle, true);
            data.setResize(i, p);
            return stop(e);
          });
        })(data, $(this), i);
      });

      data.handle8.bind('mousedown.imgfocus', function(e) {
        var p = point(e, data.handle8);
        data.setMove(p);
        return stop(e);
      });

      return data;
    },

    setResize: function(i, offset) {
      var data = this.unbindAll(),
        m = R.MAP[i],
        c = data.constraints((i + 4) % 8);

      cursor(data.handles[i]);
      $doc.bind('mousemove.imgfocus', function(e) {
        var p = data.point(e);
        p[0] -= offset[0];
        p[1] -= offset[1];

        if (m & R.L) {
          data.selRect.left(p[0]);
        }
        else if (m & R.R) {
          data.selRect.right(p[0]);
        }

        if (m & R.T) {
          data.selRect.top(p[1]);
        }
        else if (m & R.B) {
          data.selRect.bottom(p[1]);
        }

        data.selRect.constraint(c);
        data.repaint();
        return stop(e);
      });

      return data.addMouseup();
    },

    setMove: function(offset) {
      var data = this.unbindAll(),
        c = data.constraints(true);

      cursor(data.handle8);
      $doc.bind('mousemove.imgfocus', function(e) {
        var p = data.point(e);
        p[0] -= offset[0];
        p[1] -= offset[1];
        data.selRect.location(p).constraint(c);
        data.repaint();
        return stop(e);
      });

      return data.addMouseup();
    },

    addMouseup: function() {
      var data = this;

      $doc.bind('mouseup.imgfocus', function(e) {
        if (!data.oldSelRect || !data.selRect.equals(data.oldSelRect)) {
          data.$this.trigger('change');
        }
        data.setIdle();
        return stop(e);
      });

      return data;
    },

    constraints: function(extra) {
      var c = this.rules;
      if (extra === true) {
        c.moveOnly = true;
        c.anchor = 0;
      }
      else {
        c.moveOnly = false;
        c.anchor = extra || 0;
      }
      return c;
    },

    repaint: function() {
      var r = this.selRect;
      if (r && !r.isEmpty()) {
        r.applyTo(this.selBox.show());
        this.clipBox.show().css('clip', 'rect(' + r.y + 'px ' + r.right() + 'px ' + r.bottom() + 'px ' + r.x + 'px)');
      }
      else {
        this.selBox.hide();
        this.clipBox.hide();
      }
      return this;
    },

    getSel: function() {
      return (this.selRect) ?
        this.selRect.clone().scale(1 / this.scale[0], 1 / this.scale[1]).round().constraint({minSize: [1, 1]}).toArray() : null;
    },

    setSel: function(sel) {
      this.selRect = (sel) ? new Rectangle(sel).scale(this.scale).constraint(this.constraints()) : null;
      return this.repaint().setIdle();
    }
  };
  //~Data methods.



  // Plugin methods.
  var methods = {

    _init: function(options) {
      if (!$doc) {
        $doc = $(document);
        $html = $('html');
      }

      return this.each(function() {
        var $this = $(this);
        var data = $this.data('imgfocus');

        if (!data) {

          // Create elements.
          var size = [$this.width(), $this.height()];
          var wrapper = div().addClass('imgfocus-wrapper');
          var img = $('<img />').addClass('imgfocus-img').attr('src', $this.attr('src')).appendTo(wrapper);
          var clipBox = div().addClass('imgfocus-box imgfocus-clipbox').appendTo(wrapper).append(img.clone()).hide();
          var minBox = box('minbox', wrapper), maxBox = box('maxbox', wrapper), selBox = box('selbox', wrapper);
          var handles = [];
          for (var i = 0; i < 8; i++) {
            handles[i] = div().addClass('imgfocus-resize imgfocus-handle imgfocus-handle-' + i)
              .addClass((i % 2 == 0) ? 'imgfocus-resize-corner' : 'imgfocus-resize-side').appendTo(selBox);
          }
          var handle8 = div().addClass('imgfocus-move imgfocus-handle').prependTo(selBox);
          wrapper.insertAfter($this.hide());

          // Save data.
          data = $.extend({
            $this: $this,
            size: size,
            wrapper: wrapper,
            clipBox: clipBox,
            minBox: minBox,
            maxBox: maxBox,
            selBox: selBox,
            handles: handles,
            handle8: handle8,
            targets: wrapper.find('.imgfocus-handle').andSelf().add(document),
            selRect: null,
            options: {}
          }, _methods);
          $this.data('imgfocus', data);
        }

        // Set options.
        $this.imgfocus('options', options);

        // Reset events.
        data.setIdle();
      });
    },

    options: function(options) {
      options = options || {};
      return this.each(function() {
        var $this = $(this);
        var data = $this.data('imgfocus');

        // Process options.
        var o = $.extend(data.options, options), s = data.size;
        var bs = o.boxSize || [s[0], s[1]];
        var rs = o.realSize || [s[0], s[1]];
        if (!bs.length) {
          bs = [bs, bs];
        }
        var r = new R(0, 0, bs[0], bs[1]).ratio(s[0] / s[1]), r0 = r.clone();
        s = [r.width, r.height];
        var sc = data.scale = [s[0] / rs[0], s[1] / rs[1]];

        var rules = {};
        rules.maxRect = r = new R(o.maxRect).scale(sc).intersection(r).ifEmpty(r);

        rules.maxSize = (o.maxSize) ?
          [Math.max(0, Math.min(r.width, o.maxSize[0] * sc[0])), Math.max(0, Math.min(r.height, o.maxSize[1] * sc[1]))] : [r.width, r.height];

        rules.minRect = new R(o.minRect).scale(sc).intersection(r);
        var z = rules.minRect.size();
        if (rules.minRect.isEmpty()) {
          rules.minRect = null;
          z = [0, 0];
        }

        rules.minSize = z = (o.minSize) ?
          [Math.min(r.width, Math.max(z[0], o.minSize[0] * sc[0])), Math.min(r.height, Math.max(z[1], o.minSize[1] * sc[1]))] : z;

        if (o.ratio && !rules.minRect) {
          var a = ((typeof o.ratio == 'number') && o.ratio > 0) ? o.ratio : 0;
          rules.ratio = (z[0] > 0 && z[1] > 0) ? z[0] / z[1] : o.ratio * sc[0] / sc[1];
        }
        else {
          rules.ratio = 0;
        }

        rules.minSize = [Math.max(rules.minSize[0], 1), Math.max(rules.minSize[1], 1)];
        data.rules = rules;

        // Update display.
        data.wrapper.width(s[0]).height(s[1]);

        if (!rules.maxRect.equals(r0)) {
          rules.maxRect.applyTo(data.maxBox.show());
        }
        else {
          data.maxBox.hide();
        }

        if (rules.minRect) {
          rules.minRect.applyTo(data.minBox.show());
        }
        else {
          data.minBox.hide();
        }

        // TODO: update selection?
      });
    },

    selection: function(sel) {
      return (sel === undefined) ? this.data('imgfocus').getSel() : this.each(function() {
        $(this).data('imgfocus').setSel(sel);
      });
    }
  };
  //~Plugin methods.



  $.fn.imgfocus = function(method) {

    if (methods[method]) {
      return methods[method].apply(this, Array.prototype.slice.call(arguments, 1));
    }
    else if (typeof method == 'object' || !method) {
      return methods._init.apply(this, arguments);
    }
    else {
      throw 'Method ' +  method + ' does not exist on jQuery.imgfocus.';
    }

  };
})(jQuery);
