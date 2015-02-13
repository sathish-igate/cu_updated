/* Author:

*/

/*
 * jQuery Easing v1.3 - http://gsgd.co.uk/sandbox/jquery/easing/
 *
 * Uses the built in easing capabilities added In jQuery 1.1
 * to offer multiple easing options
 *
 * TERMS OF USE - jQuery Easing
 * 
 * Open source under the BSD License. 
 * 
 * Copyright å© 2008 George McGinley Smith
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of 
 * conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or other materials 
 * provided with the distribution.
 * 
 * Neither the name of the author nor the names of contributors may be used to endorse 
 * or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
*/

// t: current time, b: begInnIng value, c: change In value, d: duration
jQuery.easing['jswing'] = jQuery.easing['swing'];

jQuery.extend( jQuery.easing,
{
	def: 'easeOutQuad',
	swing: function (x, t, b, c, d) {
		//alert(jQuery.easing.default);
		return jQuery.easing[jQuery.easing.def](x, t, b, c, d);
	},
	easeInQuad: function (x, t, b, c, d) {
		return c*(t/=d)*t + b;
	},
	easeOutQuad: function (x, t, b, c, d) {
		return -c *(t/=d)*(t-2) + b;
	},
	easeInOutQuad: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return c/2*t*t + b;
		return -c/2 * ((--t)*(t-2) - 1) + b;
	},
	easeInCubic: function (x, t, b, c, d) {
		return c*(t/=d)*t*t + b;
	},
	easeOutCubic: function (x, t, b, c, d) {
		return c*((t=t/d-1)*t*t + 1) + b;
	},
	easeInOutCubic: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return c/2*t*t*t + b;
		return c/2*((t-=2)*t*t + 2) + b;
	},
	easeInQuart: function (x, t, b, c, d) {
		return c*(t/=d)*t*t*t + b;
	},
	easeOutQuart: function (x, t, b, c, d) {
		return -c * ((t=t/d-1)*t*t*t - 1) + b;
	},
	easeInOutQuart: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
		return -c/2 * ((t-=2)*t*t*t - 2) + b;
	},
	easeInQuint: function (x, t, b, c, d) {
		return c*(t/=d)*t*t*t*t + b;
	},
	easeOutQuint: function (x, t, b, c, d) {
		return c*((t=t/d-1)*t*t*t*t + 1) + b;
	},
	easeInOutQuint: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
		return c/2*((t-=2)*t*t*t*t + 2) + b;
	},
	easeInSine: function (x, t, b, c, d) {
		return -c * Math.cos(t/d * (Math.PI/2)) + c + b;
	},
	easeOutSine: function (x, t, b, c, d) {
		return c * Math.sin(t/d * (Math.PI/2)) + b;
	},
	easeInOutSine: function (x, t, b, c, d) {
		return -c/2 * (Math.cos(Math.PI*t/d) - 1) + b;
	},
	easeInExpo: function (x, t, b, c, d) {
		return (t==0) ? b : c * Math.pow(2, 10 * (t/d - 1)) + b;
	},
	easeOutExpo: function (x, t, b, c, d) {
		return (t==d) ? b+c : c * (-Math.pow(2, -10 * t/d) + 1) + b;
	},
	easeInOutExpo: function (x, t, b, c, d) {
		if (t==0) return b;
		if (t==d) return b+c;
		if ((t/=d/2) < 1) return c/2 * Math.pow(2, 10 * (t - 1)) + b;
		return c/2 * (-Math.pow(2, -10 * --t) + 2) + b;
	},
	easeInCirc: function (x, t, b, c, d) {
		return -c * (Math.sqrt(1 - (t/=d)*t) - 1) + b;
	},
	easeOutCirc: function (x, t, b, c, d) {
		return c * Math.sqrt(1 - (t=t/d-1)*t) + b;
	},
	easeInOutCirc: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return -c/2 * (Math.sqrt(1 - t*t) - 1) + b;
		return c/2 * (Math.sqrt(1 - (t-=2)*t) + 1) + b;
	},
	easeInElastic: function (x, t, b, c, d) {
		var s=1.70158;var p=0;var a=c;
		if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
		if (a < Math.abs(c)) { a=c; var s=p/4; }
		else var s = p/(2*Math.PI) * Math.asin (c/a);
		return -(a*Math.pow(2,10*(t-=1)) * Math.sin( (t*d-s)*(2*Math.PI)/p )) + b;
	},
	easeOutElastic: function (x, t, b, c, d) {
		var s=1.70158;var p=0;var a=c;
		if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
		if (a < Math.abs(c)) { a=c; var s=p/4; }
		else var s = p/(2*Math.PI) * Math.asin (c/a);
		return a*Math.pow(2,-10*t) * Math.sin( (t*d-s)*(2*Math.PI)/p ) + c + b;
	},
	easeInOutElastic: function (x, t, b, c, d) {
		var s=1.70158;var p=0;var a=c;
		if (t==0) return b;  if ((t/=d/2)==2) return b+c;  if (!p) p=d*(.3*1.5);
		if (a < Math.abs(c)) { a=c; var s=p/4; }
		else var s = p/(2*Math.PI) * Math.asin (c/a);
		if (t < 1) return -.5*(a*Math.pow(2,10*(t-=1)) * Math.sin( (t*d-s)*(2*Math.PI)/p )) + b;
		return a*Math.pow(2,-10*(t-=1)) * Math.sin( (t*d-s)*(2*Math.PI)/p )*.5 + c + b;
	},
	easeInBack: function (x, t, b, c, d, s) {
		if (s == undefined) s = 1.70158;
		return c*(t/=d)*t*((s+1)*t - s) + b;
	},
	easeOutBack: function (x, t, b, c, d, s) {
		if (s == undefined) s = 1.70158;
		return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
	},
	easeInOutBack: function (x, t, b, c, d, s) {
		if (s == undefined) s = 1.70158; 
		if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525))+1)*t - s)) + b;
		return c/2*((t-=2)*t*(((s*=(1.525))+1)*t + s) + 2) + b;
	},
	easeInBounce: function (x, t, b, c, d) {
		return c - jQuery.easing.easeOutBounce (x, d-t, 0, c, d) + b;
	},
	easeOutBounce: function (x, t, b, c, d) {
		if ((t/=d) < (1/2.75)) {
			return c*(7.5625*t*t) + b;
		} else if (t < (2/2.75)) {
			return c*(7.5625*(t-=(1.5/2.75))*t + .75) + b;
		} else if (t < (2.5/2.75)) {
			return c*(7.5625*(t-=(2.25/2.75))*t + .9375) + b;
		} else {
			return c*(7.5625*(t-=(2.625/2.75))*t + .984375) + b;
		}
	},
	easeInOutBounce: function (x, t, b, c, d) {
		if (t < d/2) return jQuery.easing.easeInBounce (x, t*2, 0, c, d) * .5 + b;
		return jQuery.easing.easeOutBounce (x, t*2-d, 0, c, d) * .5 + c*.5 + b;
	}
});

 
 
/*
 * Superfish v1.4.8 - jQuery menu widget
 * Copyright (c) 2008 Joel Birch
 *
 * Dual licensed under the MIT and GPL licenses:
 * 	http://www.opensource.org/licenses/mit-license.php
 * 	http://www.gnu.org/licenses/gpl.html
 *
 * CHANGELOG: http://users.tpg.com.au/j_birch/plugins/superfish/changelog.txt
 */

;(function($){
	$.fn.superfish = function(op){

		var sf = $.fn.superfish,
			c = sf.c,
			$arrow = $(['<span class="',c.arrowClass,'"> &#187;</span>'].join('')),
			over = function(){
				var $$ = $(this), menu = getMenu($$);
				clearTimeout(menu.sfTimer);
				$$.showSuperfishUl().siblings().hideSuperfishUl();
			},
			out = function(){
				var $$ = $(this), menu = getMenu($$), o = sf.op;
				clearTimeout(menu.sfTimer);
				menu.sfTimer=setTimeout(function(){
					o.retainPath=($.inArray($$[0],o.$path)>-1);
					$$.hideSuperfishUl();
					if (o.$path.length && $$.parents(['li.',o.hoverClass].join('')).length<1){over.call(o.$path);}
				},o.delay);	
			},
			getMenu = function($menu){
				var menu = $menu.parents(['ul.',c.menuClass,':first'].join(''))[0];
				sf.op = sf.o[menu.serial];
				return menu;
			},
			addArrow = function($a){ $a.addClass(c.anchorClass).append($arrow.clone()); };
			
		return this.each(function() {
			var s = this.serial = sf.o.length;
			var o = $.extend({},sf.defaults,op);
			o.$path = $('li.'+o.pathClass,this).slice(0,o.pathLevels).each(function(){
				$(this).addClass([o.hoverClass,c.bcClass].join(' '))
					.filter('li:has(ul)').removeClass(o.pathClass);
			});
			sf.o[s] = sf.op = o;
			
			$('li:has(ul)',this)[($.fn.hoverIntent && !o.disableHI) ? 'hoverIntent' : 'hover'](over,out).each(function() {
				if (o.autoArrows) addArrow( $('>a:first-child',this) );
			})
			.not('.'+c.bcClass)
				.hideSuperfishUl();
			
			var $a = $('a',this);
			$a.each(function(i){
				var $li = $a.eq(i).parents('li');
				$a.eq(i).focus(function(){over.call($li);}).blur(function(){out.call($li);});
			});
			o.onInit.call(this);
			
		}).each(function() {
			var menuClasses = [c.menuClass];
			if (sf.op.dropShadows  && !($.browser.msie && $.browser.version < 7)) menuClasses.push(c.shadowClass);
			$(this).addClass(menuClasses.join(' '));
		});
	};

	var sf = $.fn.superfish;
	sf.o = [];
	sf.op = {};
	sf.IE7fix = function(){
		var o = sf.op;
		if ($.browser.msie && $.browser.version > 6 && o.dropShadows && o.animation.opacity!=undefined)
			this.toggleClass(sf.c.shadowClass+'-off');
		};
	sf.c = {
		bcClass     : 'sf-breadcrumb',
		menuClass   : 'sf-js-enabled',
		anchorClass : 'sf-with-ul',
		arrowClass  : 'sf-sub-indicator',
		shadowClass : 'sf-shadow'
	};
	sf.defaults = {
		hoverClass	: 'sfHover',
		pathClass	: 'overideThisToUse',
		pathLevels	: 1,
		delay		: 300,
		animation	: {opacity:'show'},
		speed		: 'normal',
		autoArrows	: false,
		dropShadows : true,
		disableHI	: false,		// true disables hoverIntent detection
		onInit		: function(){}, // callback functions
		onBeforeShow: function(){},
		onShow		: function(){},
		onHide		: function(){}
	};
	$.fn.extend({
		hideSuperfishUl : function(){
			var o = sf.op,
				not = (o.retainPath===true) ? o.$path : '';
			o.retainPath = false;
			var $ul = $(['li.',o.hoverClass].join(''),this).add(this).not(not).removeClass(o.hoverClass)
					.find('>ul').hide().css('visibility','hidden');
			o.onHide.call($ul);
			return this;
		},
		showSuperfishUl : function(){
			var o = sf.op,
				sh = sf.c.shadowClass+'-off',
				$ul = this.addClass(o.hoverClass)
					.find('>ul:hidden').css('visibility','visible');
			sf.IE7fix.call($ul);
			o.onBeforeShow.call($ul);
			$ul.animate(o.animation,o.speed,function(){ sf.IE7fix.call($ul); o.onShow.call($ul); });
			return this;
		}
	});

})(jQuery);

$(document).ready(function() {

	//Homepage scroll (main content slider)
	$("#homescroll")
		.scrollable({
			circular: true,
			speed: 1000,
			easing: 'easeInOutExpo'
		})
		.autoscroll({
			autoplay: true,
			interval: 6000,
			autopause: true
		});
		
	$(".browse").click(function() {
		$("#homescroll").data("scrollable").stop();
	});

	// Navigation menu
	$('ul.sf-menu').superfish();


	// more/less functionality
	$('span.more').hide().before('<a class="more">More</a>').append('<a class="less">Less</a>');
	$('a.more').click(function(event) {
		event.preventDefault();
		$(this).hide();
                $(this).next().show();
	});
   	$('a.less').click(function(event) {
		event.preventDefault();
		$(this).parent().hide().prev('a.more').show();
	});
	
	$('span.infomore').hide().before('<a class="more">More</a>').append('<a class="less">Less</a>');
	$('a.more').click(function(event) {
		event.preventDefault();
		$(this).hide();
                $(this).next().show();
		$(".infomoreh2").css("height", "auto");
	});
   	$('a.less').click(function(event) {
		event.preventDefault();
		$(this).parent().hide().prev('a.more').show();
		$(".infomoreh2").css("height", "30px");
	});
	
	$('span.infomorep').hide().before('<a class="more">More</a>').append('<a class="less">Less</a>');
	$('a.more').click(function(event) {
		event.preventDefault();
		$(this).hide();
                $(this).next().show();
		$(".infomorebody").css("height", "auto");
	});
   	$('a.less').click(function(event) {
		event.preventDefault();
		$(this).parent().hide().prev('a.more').show();
		$(".infomorebody").css("height", "300px");
	});

	$('span.infomore_left_span').hide().before('<a class="left_more">More</a>').append('<a class="left_less">Less</a>');
	$('a.left_more').click(function(event) {
		event.preventDefault();
		$(this).hide();
                $(this).next().show();
		$(".infomore_left_desc.").css("height", "auto");
	});
   	$('a.left_less').click(function(event) {
		event.preventDefault();
		$(this).parent().hide().prev('a.left_more').show();
		$(".infomore_left_desc").css("height", "120px");
	});

	$('span.leftdescmore').hide().before('<a class="left_more">More</a>').append('<a class="left_less">Less</a>');
	$('a.left_more').click(function(event) {
		event.preventDefault();
		$(this).hide();
                $(this).next().show();
		$(".leftdesc").css("height", "auto");
	});
   	$('a.left_less').click(function(event) {
		event.preventDefault();
		$(this).parent().hide().prev('a.left_more').show();
		$(".leftdesc").css("height", "155px");
	});

	$('span.transcriptdescmore').hide().before('<a class="more">More</a>').append('<a class="less">Less</a>');
	$('a.more').click(function(event) {
		event.preventDefault();
		$(this).hide();
                $(this).next().show();
		$(".transcriptdesc").css("height", "auto");
	});
   	$('a.less').click(function(event) {
		event.preventDefault();
		$(this).parent().hide().prev('a.more').show();
		$(".transcriptdesc").css("height", "80px");
	});

	$('span.blackdescmore').hide().before('<a class="right_more">More</a>').append('<a class="right_less">Less</a>');
	$('a.right_more').click(function(event) {
		event.preventDefault();
		$(this).hide();
                $(this).next().show();
		$(".blackdesc").css("height", "auto");
	});
   	$('a.right_less').click(function(event) {
		event.preventDefault();
		$(this).parent().hide().prev('a.right_more').show();
		$(".blackdesc").css("height", "250px");
	});
	
	$('span.issuedescspan').hide().before('<a class="issuedesc_more">More</a>').append('<a class="issuedesc_less">Less</a>');
	$('a.issuedesc_more').click(function(event) {
		event.preventDefault();
		$(this).hide();
                $(this).next().show();
		$(".issuedesc").css("height", "auto");
	});
   	$('a.issuedesc_less').click(function(event) {
		event.preventDefault();
		$(this).parent().hide().prev('a.issuedesc_more').show();
		$(".issuedesc").css("height", "150px");
	});
	
	// Extras overlay 
	$("a[rel=extr_overlay]").fancybox({
		'transitionIn'		: 'none',
		'transitionOut'	: 'none',
		'titlePosition' 	: 'inside',
		'overlayColor'		: '#000',
		'overlayOpacity'	: 0.7,
		'titleFormat'		: function(title, currentArray, currentIndex, currentOpts) {
			return '<span id="fancybox-title-over">Image ' + (currentIndex + 1) + ' / ' + currentArray.length + (title.length ? ' &nbsp; ' + title : '') + '</span>';
		}
	});

	// Nomination form TV provider
	$('#nomineeProvider').change(function(e) {
		checkProvider();
	});
	
	checkProvider();
	
	$(".quicktabs-tabs li a").click(function(){
		var a_id = $(this).attr("id"); 
		var Fst = a_id.lastIndexOf("-");  
		var Snd = a_id.lastIndexOf("-", Fst-1);
		var a_id2 = a_id.substr(Snd);
		//alert(a_id+'|'+Fst+'-'+Snd+'-'+a_id2);
		if ($("#quicktabs-tabpage"+a_id2).has("div.quick_tab_redirect").length > 0) {
			var link = $("#quicktabs-tabpage"+a_id2+" div.quick_tab_redirect").text();
			window.location = link;
		}
	});
});

// Pledge form processing
function submitPledgeForm() {
	$.post("ajax.php", $("#pledgeForm").serialize(), function(data) {});
}

// Nominate form processing
function submitNominateForm() {
/*
	if(isOtherSelected() && !isOtherChecked()) {
		alert('Please check the nominee television provider checkbox');
		return;
	}
*/	
	$.post("ajax.php", $("#nominateForm").serialize(), function(data) {
		$('.nominateFormMain').html('Thank you for submitting your nomination for the Characters Unite Awards.');
	});
}

function checkProvider() {
	showProviderCheckbox(isOtherSelected());
}

function isOtherSelected() {
	var $select	= $('#nomineeProvider'),
	    value 	= $select.find('option[value="' + $select.val() + '"]').text();
	
	return (value.toLowerCase().indexOf('other') !== -1);
}

function isOtherChecked() {
	return $('#nominateTVproviderCheck input').prop('checked');
}

function showProviderCheckbox(b) {
	if(b) {
		$('#nominateTVproviderCheck').show()
	} else {
		$('#nominateTVproviderCheck').hide();
		$('#nominateTVproviderCheck input').prop('checked', '')
	}  
}



// customStyle pulldown elements
(function($){
 $.fn.extend({
 
 	customStyle : function(options) {
	  if(!$.browser.msie || ($.browser.msie&&$.browser.version>6)){
	  return this.each(function() {
	  
			var currentSelected = $(this).find(':selected');
			$(this).after('<span class="customStyleSelectBox"><span class="customStyleSelectBoxInner">'+currentSelected.text()+'</span></span>').css({position:'absolute', opacity:0,fontSize:$(this).next().css('font-size')});
			var selectBoxSpan = $(this).next();
			var selectBoxWidth = parseInt($(this).width()) - parseInt(selectBoxSpan.css('padding-left')) -parseInt(selectBoxSpan.css('padding-right'));			
			var selectBoxSpanInner = selectBoxSpan.find(':first-child');
			selectBoxSpan.css({display:'inline-block'});
			selectBoxSpanInner.css({width:selectBoxWidth, display:'inline-block'});
			var selectBoxHeight = parseInt(selectBoxSpan.height()) + parseInt(selectBoxSpan.css('padding-top')) + parseInt(selectBoxSpan.css('padding-bottom'));
			$(this).height(selectBoxHeight).change(function(){
				// selectBoxSpanInner.text($(this).val()).parent().addClass('changed');   This was not ideal
			selectBoxSpanInner.text($(this).find(':selected').text()).parent().addClass('changed');
				// Thanks to Juarez Filho & PaddyMurphy
			});
			
	  });
	  }
	}
 });
})(jQuery);


$(document).ready(function(){	
	$('#nomineeYear').customStyle();
	$('#nomineeDay').customStyle();
	$('#nomineeMonth').customStyle();
	$('#nomineeState').customStyle();
	$('#nomineeProvider').customStyle();
	$('.home .section').click(function(){
		window.location = $(this).find('a').attr('href');
	});
	$('.home .hscontent h2, .home .hscontent p').click(function(){
		window.location = $(this).siblings('a').attr('href');
	});

	$('.kiosk_overlay a').click(function(e) {
		e.preventDefault();
		var url = $(this).attr('href');
		$.fancybox({
			'type'						: 'iframe',
			'overlayColor'		: '#000',
			'centerOnScroll'	: true,
			'overlayOpacity'	: '.75',
			'showCloseButton'	:	false,
			'href'						: url,
			'titleShow'     	: false,
			'transitionIn'		: 'fade',
			'transitionOut'		: 'fade',
			'autoDimensions'	: false,
			'width'						: 400,
			'height'					: 641,
			'scrolling'				: 'no',
			'margin'					: 0,
			'padding'					: 0		
		});
	});

});
function LeftDesc(container, ref, size, q) {
	if (ref == 'less') {
		$("."+container).css("height", "auto");
		$(".amore"+q).hide();
		$("."+container+"_"+ref).show();
	}
	if (ref == 'more') {
		$("."+container).css("height", size);
		$(".amore"+q).hide();
		$("."+container+"_"+ref).show();
	}	
}
function TDesc(container, ref, size, q) {
	if (ref == 'less') {
		$("."+container).css("height", "auto");
		$(".atmore"+q).hide();
		$("."+container+"_"+ref).show();
	}
	if (ref == 'more') {
		$("."+container).css("height", size);
		$(".atmore"+q).hide();
		$("."+container+"_"+ref).show();
	}	
}