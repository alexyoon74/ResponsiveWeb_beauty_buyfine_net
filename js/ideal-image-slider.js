/*
 * Ideal Image Slider v1.5.1
 *
 * By Gilbert Pellegrom
 * //gilbert.pellegrom.me
 *
 * Copyright (C) 2014 Dev7studios
 * https://raw.githubusercontent.com/gilbitron/Ideal-Image-Slider/master/LICENSE
 */
var IdealImageSlider = (function() {
	"use strict";
	
	var g_shouldAnimate = false;//self var - defautl true
	var selfActLoc = 'detail';
	var selfMaxSize = 700;//self var
	var selfAddTouchSpeed = 0;//self var

	/*
	 * requestAnimationFrame polyfill
	 */
	var _requestAnimationFrame = function(win, t) {
		return win["r" + t] || win["webkitR" + t] || win["mozR" + t] || win["msR" + t] || function(fn) {
			setTimeout(fn, 1000 / 60);
		};
	}(window, 'equestAnimationFrame');

	/**
	 * Behaves the same as setTimeout except uses requestAnimationFrame() where possible for better performance
	 * @param {function} fn The callback function
	 * @param {int} delay The delay in milliseconds
	 */
	var _requestTimeout = function(fn, delay) {
		var start = new Date().getTime(),
			handle = {};

		function loop() {
			var current = new Date().getTime(),
				delta = current - start;

			if (delta >= delay) {
				fn.call();
			} else {
				handle.value = _requestAnimationFrame(loop);
			}
		}

		handle.value = _requestAnimationFrame(loop);
		return handle;
	};

	/*
	 * Helper functions
	 */
	var _isType = function(type, obj) {
		var _class = Object.prototype.toString.call(obj).slice(8, -1);
		return obj !== undefined && obj !== null && _class === type;
	};

	var _isInteger = function(x) {
		return Math.round(x) === x;
	};

	var _deepExtend = function(out) {
		out = out || {};
		for (var i = 1; i < arguments.length; i++) {
			var obj = arguments[i];
			if (!obj)
				continue;
			for (var key in obj) {
				if (obj.hasOwnProperty(key)) {
					if (_isType('Object', obj[key]) && obj[key] !== null)
						_deepExtend(out[key], obj[key]);
					else
						out[key] = obj[key];
				}
			}
		}
		return out;
	};

	var _hasClass = function(el, className) {
		if (!className) return false;
		if (el.classList) {
			return el.classList.contains(className);
		} else {
			return new RegExp('(^| )' + className + '( |$)', 'gi').test(el.className);
		}
	};

	var _addClass = function(el, className) {
		if (!className) return;
		if (el.classList) {
			el.classList.add(className);
		} else {
			el.className += ' ' + className;
		}
	};

	var _removeClass = function(el, className) {
		if (!className) return;
		if (el.classList) {
			el.classList.remove(className);
		} else {
			el.className = el.className.replace(new RegExp('(^|\\b)' + className.split(' ').join('|') + '(\\b|$)', 'gi'), ' ');
		}
	};

	var _toArray = function(obj) {
		return Array.prototype.slice.call(obj);
	};

	var _arrayRemove = function(array, from, to) {
		var rest = array.slice((to || from) + 1 || array.length);
		array.length = from < 0 ? array.length + from : from;
		return array.push.apply(array, rest);
	};

	var _addEvent = function(object, type, callback) {
		if (object === null || typeof(object) === 'undefined') return;

		if (object.addEventListener) {
			object.addEventListener(type, callback, false);
		} else if (object.attachEvent) {
			object.attachEvent("on" + type, callback);
		} else {
			object["on" + type] = callback;
		}
	};

	var _loadImg = function(slide, callback) {
		if (!slide.style.backgroundImage) {
			var img = new Image();
			img.setAttribute('src', slide.getAttribute('data-src'));
			img.onload = function() {
				
				/* self logic start */
				var natural_width = this.naturalWidth;
				var natural_height = this.naturalHeight;
				//console.log('natural_width='+natural_width+' : natural_height='+natural_height+' : img.width='+img.width+' : img.height='+img.height);
				if(selfMaxSize>0)
				{
					if(natural_width == natural_height)
					{					
						if(selfActLoc=='zoom' || selfActLoc=='contain')
						{
							slide.style.backgroundSize = 'contain';	
						}
						else
						{
							if(natural_width > 699)
							{
								slide.style.backgroundSize = 'contain';
							}
						}
					}
					else
					{
						slide.style.backgroundSize = 'contain';
					}
				}
				slide.style.backgroundImage = 'url(' + slide.getAttribute('data-src') + ')';
				slide.setAttribute('data-actual-width', natural_width);
				slide.setAttribute('data-actual-height', natural_height);
				if (typeof(callback) === 'function') callback(this);
				/* self logic end */
				/*
slide.style.backgroundImage = 'url(' + slide.getAttribute('data-src') + ')';
				slide.setAttribute('data-actual-width', this.naturalWidth);
				slide.setAttribute('data-actual-height', this.naturalHeight);
				if (typeof(callback) === 'function') callback(this);
*/
			};
		}
	};

	var _isHighDPI = function() {
		var mediaQuery = "(-webkit-min-device-pixel-ratio: 1.5),(min--moz-device-pixel-ratio: 1.5),(-o-min-device-pixel-ratio: 3/2),(min-resolution: 1.5dppx)";
		if (window.devicePixelRatio > 1)
			return true;
		if (window.matchMedia && window.matchMedia(mediaQuery).matches)
			return true;
		return false;
	};

	var _translate = function(slide, dist, speed) {
		slide.style.webkitTransitionDuration =
			slide.style.MozTransitionDuration =
			slide.style.msTransitionDuration =
			slide.style.OTransitionDuration =
			slide.style.transitionDuration = speed + 'ms';

		slide.style.webkitTransform =
			slide.style.MozTransform =
			slide.style.msTransform =
			slide.style.OTransform = 'translateX(' + dist + 'px)';
	};

	var _unTranslate = function(slide) {
		slide.style.removeProperty('-webkit-transition-duration');
		slide.style.removeProperty('transition-duration');

		slide.style.removeProperty('-webkit-transform');
		slide.style.removeProperty('-ms-transform');
		slide.style.removeProperty('transform');
	};

	var _animate = function(item) {
		var duration = item.time,
			end = +new Date() + duration;

		var step = function() {
			var current = +new Date(),
				remaining = end - current;

			if (remaining < 60) {
				item.run(1); //1 = progress is at 100%
				return;
			} else {
				var progress = 1 - remaining / duration;
				item.run(progress);
			}

			_requestAnimationFrame(step);
		};
		step();
	};

	var _setContainerHeight = function(slider, shouldAnimate) {
		if (typeof shouldAnimate === 'undefined') {
			shouldAnimate = true;
		}

		// If it's a fixed height then don't change the height
		if (_isInteger(slider.settings.height)) {
			return;
		}

		var currentHeight = Math.round(slider._attributes.container.offsetHeight),
			newHeight = currentHeight;

		if (slider._attributes.aspectWidth && slider._attributes.aspectHeight) {
			// Aspect ratio
			newHeight = (slider._attributes.aspectHeight / slider._attributes.aspectWidth) * slider._attributes.container.offsetWidth;
		} else {
			// Auto
			var width = slider._attributes.currentSlide.getAttribute('data-actual-width');
			var height = slider._attributes.currentSlide.getAttribute('data-actual-height');

			if (width && height) {
				newHeight = (height / width) * slider._attributes.container.offsetWidth;
			}
		}

		var maxHeight = parseInt(slider.settings.maxHeight, 10);
		if (maxHeight && newHeight > maxHeight) {
			newHeight = maxHeight;
		}

		newHeight = Math.round(newHeight);
		if(selfMaxSize>0)
		{
			newHeight = selfMaxSize;//slef var
		}
		//console.log(selfMaxSize+' : '+width+' : '+height+' : '+newHeight+' : '+currentHeight+' : '+g_shouldAnimate);
		if (newHeight === currentHeight) {
			return;
		}
		
		if(!g_shouldAnimate)
		{
			shouldAnimate = false;
		}
		//console.log('shouldAnimate='+shouldAnimate);
		
		//alert(shouldAnimate);
		
		if (shouldAnimate) {
			_animate({
				time: slider.settings.transitionDuration,
				run: function(progress) {
					slider._attributes.container.style.height = Math.round(progress * (newHeight - currentHeight) + currentHeight) + 'px';
				}
			});
		} else {
			slider._attributes.container.style.height = newHeight + 'px';
		}
	};
	
	var _touch = {

		vars: {
			start: {},
			delta: {},
			isScrolling: undefined,
			direction: null
		},

		start: function(event) {
			if (_hasClass(this._attributes.container, this.settings.classes.animating)) return;

			var touches = event.touches[0];
			_touch.vars.start = {
				x: touches.pageX,
				y: touches.pageY,
				time: +new Date()
			};
			_touch.vars.delta = {};
			_touch.vars.isScrolling = undefined;
			_touch.vars.direction = null;

			//alert('1');
			this.stop(); // Stop slider
			this.settings.beforeChange.apply(this);
			_addClass(this._attributes.container, this.settings.classes.touching);
		},

		move: function(event) {
			if (_hasClass(this._attributes.container, this.settings.classes.animating)) return;
			// Ensure swiping with one touch and not pinching
			if (event.touches.length > 1 || event.scale && event.scale !== 1) return;
			var touches = event.touches[0];
			_touch.vars.delta = {
				x: touches.pageX - _touch.vars.start.x,
				y: touches.pageY - _touch.vars.start.y
			};
			
			if (typeof _touch.vars.isScrolling == 'undefined') {
				_touch.vars.isScrolling = !!(_touch.vars.isScrolling || Math.abs(_touch.vars.delta.x) < Math.abs(_touch.vars.delta.y));
			}

			// If user is not trying to scroll vertically
			if (!_touch.vars.isScrolling) {
				event.preventDefault(); // Prevent native scrolling

				_translate(this._attributes.previousSlide, _touch.vars.delta.x - this._attributes.previousSlide.offsetWidth, 0);
				_translate(this._attributes.currentSlide, _touch.vars.delta.x, 0);
				_translate(this._attributes.nextSlide, _touch.vars.delta.x + this._attributes.currentSlide.offsetWidth, 0);
			}
		},

		end: function(event) {
			if (_hasClass(this._attributes.container, this.settings.classes.animating)) return;
			var duration = +new Date() - _touch.vars.start.time;
			// Determine if slide attempt triggers next/prev slide
			//var isChangeSlide = Number(duration) < 250 && Math.abs(_touch.vars.delta.x) > 20 || Math.abs(_touch.vars.delta.x) > this._attributes.currentSlide.offsetWidth / 2;
			/* self logic start	*/
			//console.log('ideal touch end');
			var touch_var_x = Math.abs(_touch.vars.delta.x);
			var is_slide_offset_w = this._attributes.currentSlide.offsetWidth / 5;
			//alert(Number(duration)+' / '+touch_var_x+' / '+is_slide_offset_w);
			var isChangeSlide = Number(duration) < 250 && touch_var_x > 20 || touch_var_x > is_slide_offset_w;
			/* self logic end	*/
			//alert(isChangeSlide);

			var direction = _touch.vars.delta.x < 0 ? 'next' : 'previous';
			var speed = this.settings.transitionDuration ? this.settings.transitionDuration / 2 : 0;
			//speed = speed-100;
			speed = 150;
			if(selfAddTouchSpeed > 0)
			{
				//speed = speed+selfAddTouchSpeed;//self
			}
			//alert(speed);

			// If not scrolling vertically
			if (!_touch.vars.isScrolling) {
				if (isChangeSlide) {
					_touch.vars.direction = direction;

					if (_touch.vars.direction == 'next') {
						_translate(this._attributes.currentSlide, -this._attributes.currentSlide.offsetWidth, speed);
						_translate(this._attributes.nextSlide, 0, speed);
					} else {
						_translate(this._attributes.previousSlide, 0, speed);
						_translate(this._attributes.currentSlide, this._attributes.currentSlide.offsetWidth, speed);
					}

					_requestTimeout(_touch.transitionEnd.bind(this), speed);
				} else {
					// Slides return to original position
					if (direction == 'next') {
						_translate(this._attributes.currentSlide, 0, speed);
						_translate(this._attributes.nextSlide, this._attributes.currentSlide.offsetWidth, speed);
					} else {
						_translate(this._attributes.previousSlide, -this._attributes.previousSlide.offsetWidth, speed);
						_translate(this._attributes.currentSlide, 0, speed);
					}
					
					//_requestTimeout(_touch.sefVarTransitionNotEnd.bind(this), speed);
				}

				if (speed) {
					_addClass(this._attributes.container, this.settings.classes.animating);
					_requestTimeout(function() {
						_removeClass(this._attributes.container, this.settings.classes.animating);
					}.bind(this), speed);
				}
				//console.log('ideal touch end');
			}
			if(typeof self_var_is_app_pull_to_refresh!="undefined" && typeof self_var_set_app_pull_to_refresh!="undefined")
			{
				//this.settings.afterChange.apply(this);
			}
		},
		
		transitionEnd: function(event) {			
			if (_touch.vars.direction) {
				_unTranslate(this._attributes.previousSlide);
				_unTranslate(this._attributes.currentSlide);
				_unTranslate(this._attributes.nextSlide);
				_removeClass(this._attributes.container, this.settings.classes.touching);

				_removeClass(this._attributes.previousSlide, this.settings.classes.previousSlide);
				_removeClass(this._attributes.currentSlide, this.settings.classes.currentSlide);
				_removeClass(this._attributes.nextSlide, this.settings.classes.nextSlide);
				this._attributes.currentSlide.setAttribute('aria-hidden', 'true');

				var slides = this._attributes.slides,
					index = slides.indexOf(this._attributes.currentSlide);

				if (_touch.vars.direction == 'next') {
					this._attributes.previousSlide = this._attributes.currentSlide;
					this._attributes.currentSlide = slides[index + 1];
					this._attributes.nextSlide = slides[index + 2];
					if (typeof this._attributes.currentSlide === 'undefined' &&
						typeof this._attributes.nextSlide === 'undefined') {
						this._attributes.currentSlide = slides[0];
						this._attributes.nextSlide = slides[1];
					} else {
						if (typeof this._attributes.nextSlide === 'undefined') {
							this._attributes.nextSlide = slides[0];
						}
					}

					_loadImg(this._attributes.nextSlide);
				} else {
					this._attributes.nextSlide = this._attributes.currentSlide;
					this._attributes.previousSlide = slides[index - 2];
					this._attributes.currentSlide = slides[index - 1];
					if (typeof this._attributes.currentSlide === 'undefined' &&
						typeof this._attributes.previousSlide === 'undefined') {
						this._attributes.currentSlide = slides[slides.length - 1];
						this._attributes.previousSlide = slides[slides.length - 2];
					} else {
						if (typeof this._attributes.previousSlide === 'undefined') {
							this._attributes.previousSlide = slides[slides.length - 1];
						}
					}

					_loadImg(this._attributes.previousSlide);
				}

				_addClass(this._attributes.previousSlide, this.settings.classes.previousSlide);
				_addClass(this._attributes.currentSlide, this.settings.classes.currentSlide);
				_addClass(this._attributes.nextSlide, this.settings.classes.nextSlide);
				this._attributes.currentSlide.setAttribute('aria-hidden', 'false');

				/* self logic start */
				/*
var s_index = this._attributes.currentSlide.getAttribute('s-index');
				s_index = parseInt(s_index);
				if(selfActLoc=='zoom' && is_parent_same_ch>0) parent.go_to_slide_assign_idx(s_index);
				var color_str = this._attributes.currentSlide.getAttribute('color-str');
				var txt_color_str = "";
				if(is_no_need_same_color_img<1 && color_str && typeof color_str!="undefined")
				{
					txt_color_str = ' &nbsp;'+color_str
				}
				var share_src = this._attributes.currentSlide.getAttribute('share-src');
				var share_bf_src = this._attributes.currentSlide.getAttribute('share-bf-src');
				if(share_src && share_bf_src && typeof share_src!="undefined" && typeof share_bf_src!="undefined")
				{
					if(typeof wx_e_imgUrl!="undefined" && typeof wx_e_bf_imgUrl!="undefined")
					{
						//console.log('reassign');
						wx_e_imgUrl = share_src;
						wx_e_bf_imgUrl = share_bf_src;
					}
					//console.log('transitionEnd func share_src='+share_src+'\n share_bf_src='+share_bf_src+'\n wx_e_imgUrl='+wx_e_imgUrl+'\n wx_e_bf_imgUrl='+wx_e_bf_imgUrl);
				}
				if(selfActLoc=='zoom')
				{
					$('#zoomImgPopup .slide-txt-info', parent.document).html(s_index+' / '+slide_img_r_ct+txt_color_str);
					if(is_parent_same_ch>0)
					{
						$('#imgSlideLayer .slide-txt-info', parent.document).html(s_index+' / '+slide_img_r_ct+txt_color_str);
					}
				}
				else
				{
					$('.slide-txt-info').html(s_index+' / '+slide_img_r_ct+txt_color_str);
					//console.log('onsale-noti-icon-1 s_index='+s_index+' / is_onsale_icon='+is_onsale_icon);
					if(is_onsale_icon > 0)
					{
						if(s_index == 1)
						{
							$('.onsale-noti-str').css('display', 'none');
							$('.onsale-noti-icon').css('display', 'block');
						}
						else
						{
							$('.onsale-noti-str').css('display', 'none');
							$('.onsale-noti-icon').css('display', 'none');
						}
					}
				}
*/
				/* self logic end */
				_setContainerHeight(this);
				this.settings.afterChange.apply(this);
			}
		}

	};

	/*
	 * Slider class
	 */
	var Slider = function(args) {
		// Defaults
		this.settings = {
			selector: '',
			height: 'auto', // "auto" | px value (e.g. 400) | aspect ratio (e.g. "16:9")
			initialHeight: 400, // for "auto" and aspect ratio
			maxHeight: null, // for "auto" and aspect ratio
			interval: 4000,
			transitionDuration: 700,//default 700
			effect: 'slide',
			disableNav: false,
			keyboardNav: true,
			previousNavSelector: '',
			nextNavSelector: '',
			selfVarMaxSize: 0, //self var
			selfVarAddTouchSpeed: 0, //self var
			selfVarActLoc: 'detail', //self var
			classes: {
				container: 'ideal-image-slider',
				slide: 'iis-slide',
				previousSlide: 'iis-previous-slide',
				currentSlide: 'iis-current-slide',
				nextSlide: 'iis-next-slide',
				previousNav: 'iis-previous-nav',
				nextNav: 'iis-next-nav',
				animating: 'iis-is-animating',
				touchEnabled: 'iis-touch-enabled',
				touching: 'iis-is-touching',
				directionPrevious: 'iis-direction-previous',
				directionNext: 'iis-direction-next'
			},
			onInit: function() {
				//console.log('onInit start');
			},
			onStart: function() {
				//console.log('onStart start');
			},
			onStop: function() {
				//console.log('onStop start');
			},
			onDestroy: function() {
				//console.log('onDestroy start');
			},
			beforeChange: function() {
				//console.log('beforeChange start');
			},
			afterChange: function() {
				//console.log('afterChange start');
			}
		};
			
		// Parse args
		if (typeof args === 'string') {
			this.settings.selector = args;
		} else if (typeof args === 'object') {
			_deepExtend(this.settings, args);
		}

		// Slider (container) element
		var sliderEl = document.querySelector(this.settings.selector);
		if (!sliderEl) return null;
		
		/* self logic start */
		//console.log('this.settings.selfVarMaxSize='+this.settings.selfVarMaxSize);
		if(this.settings.selfVarMaxSize)
		{
			if(this.settings.selfVarMaxSize > 9999)
			{
				selfMaxSize = window.innerHeight;//self var
			}
			else
			{
				selfMaxSize = this.settings.selfVarMaxSize;//self var
			}
		}
		//console.log('selfMaxSize='+selfMaxSize);
		if(this.settings.selfVarAddTouchSpeed)
		{
			selfAddTouchSpeed = this.settings.selfVarAddTouchSpeed;
		}
		if(this.settings.selfVarActLoc)
		{
			selfActLoc = this.settings.selfVarActLoc;
		}
		/* self logic end */

		// Slides
		var origChildren = _toArray(sliderEl.children),
			validSlides = [];
		sliderEl.innerHTML = '';
		Array.prototype.forEach.call(origChildren, function(slide, i) {
			if (slide instanceof HTMLImageElement || slide instanceof HTMLAnchorElement) {
				var slideEl = document.createElement('a'),
					href = '',
					target = '',
					onclick = '',
					zoom_url = '',
					color_str = '';

				if (slide instanceof HTMLAnchorElement) {
					href = slide.getAttribute('href');
					target = slide.getAttribute('target');
					onclick = slide.getAttribute('onclick');
					//alert(onclick);
					var img = slide.querySelector('img');
					if (img !== null) {
						slide = img;
					} else {
						return;
					}
				}

				if (typeof slide.dataset !== 'undefined') {
					_deepExtend(slideEl.dataset, slide.dataset);
					if (slide.dataset.src) {
						// Use data-src for on-demand loading
						slideEl.dataset.src = slide.dataset.src;
					} else {
						
						slideEl.dataset.src = slide.src;
					}

					// HiDPI support
					if (_isHighDPI() && slide.dataset['src-2x']) {
						slideEl.dataset.src = slide.dataset['src-2x'];
					}
				} else {
					// IE
					if (slide.getAttribute('data-src')) {
						slideEl.setAttribute('data-src', slide.getAttribute('data-src'));
					} else {
						slideEl.setAttribute('data-src', slide.getAttribute('src'));
					}
				}
				
				if (href) slideEl.setAttribute('href', href);
				if (target) slideEl.setAttribute('target', target);
				if (onclick) slideEl.setAttribute('onclick', onclick);
				if (slide.getAttribute('className')) _addClass(slideEl, slide.getAttribute('className'));
				if (slide.getAttribute('id')) slideEl.setAttribute('id', slide.getAttribute('id'));
				if (slide.getAttribute('title')) slideEl.setAttribute('title', slide.getAttribute('title'));
				if (slide.getAttribute('alt')) slideEl.innerHTML = slide.getAttribute('alt');
				/* self logic start */
				/*
var zoom_url = slide.getAttribute('zoom-url');
				//console.log('Slides zoom_url='+zoom_url);
				if(zoom_url && typeof zoom_url!="undefined")
				{
					slideEl.setAttribute('zoom-url', zoom_url);
				}
				var s_index = slide.getAttribute('s-index');
				if(s_index && typeof s_index!="undefined")
				{
					//console.log('color_str true='+color_str);
					slideEl.setAttribute('s-index', s_index);
				}
				s_index = parseInt(s_index);
				var share_src = slide.getAttribute('share-src');
				if(share_src && typeof share_src!="undefined")
				{
					slideEl.setAttribute('share-src', share_src);
				}
				var share_bf_src = slide.getAttribute('share-bf-src');
				if(share_bf_src && typeof share_bf_src!="undefined")
				{
					slideEl.setAttribute('share-bf-src', share_bf_src);
				}
				var color_str = slide.getAttribute('color-str');
				//console.log('Slides color_str='+color_str);
				var txt_color_str = "";
				if(is_no_need_same_color_img<1 && color_str && typeof color_str!="undefined")
				{
					//console.log('color_str true='+color_str);
					slideEl.setAttribute('color-str', color_str);
					txt_color_str = ' &nbsp;'+color_str
				}
				if(selfActLoc=='zoom')
				{
				}
				else
				{
					//console.log('onsale-noti-icon-2 s_index='+s_index+' / is_onsale_icon='+is_onsale_icon);
					if(is_onsale_icon>0 && s_index==1)
					{
						//$('.onsale-noti-str').css('display', 'block');
						//$('.onsale-noti-icon').css('display', 'block');
					}
					//if(i<1) $('.slide-txt-info').html(s_index+' / '+slide_img_r_ct+txt_color_str);
				}
*/
				/* self logic end */
				slideEl.setAttribute('role', 'tabpanel');
				slideEl.setAttribute('aria-hidden', 'true');

				slideEl.style.cssText += '-webkit-transition-duration:' + this.settings.transitionDuration + 'ms;-moz-transition-duration:' + this.settings.transitionDuration + 'ms;-o-transition-duration:' + this.settings.transitionDuration + 'ms;transition-duration:' + this.settings.transitionDuration + 'ms;';

				sliderEl.appendChild(slideEl);
				validSlides.push(slideEl);
			}
		}.bind(this));

		var slides = validSlides;
		if (slides.length <= 1) {
			sliderEl.innerHTML = '';
			//console.log('Load single image- this.settings.selfVarMaxSize='+this.settings.selfVarMaxSize+' / window.innerWidth='+window.innerWidth+' / window.innerHeight='+window.innerHeight);
			Array.prototype.forEach.call(origChildren, function(child, i) {
				/*
if (!child.style.backgroundImage) {
					child.style.width = window.innerWidth + 'px';
					child.style.height = window.innerHeight + 'px';
					child.style.backgroundSize = 'contain';
					child.style.backgroundImage = 'url(' + child.getAttribute('data-src') + ')';
					child.style.backgroundRepeat = 'no-repeat';
				}
*/
				sliderEl.appendChild(child);
			});
			//sliderEl.style.backgroundImage = 'url(' + sliderEl.getAttribute('src') + ')';
			/* self logic start */
			if(selfActLoc=='zoom')
			{
				$('.slide-txt-info', parent.document).text('1 / 1');
				//console.log('window.innerHeight='+window.innerHeight+' / zoomImgSlideLayer H='+$('#zoomImgSlideLayer').height());
				var w_h = window.innerHeight;
				var l_h = $('#zoomImgSlideLayer').height();
				if(w_h > l_h)
				{
					var img_padding = w_h - l_h;
					img_padding = Math.ceil(img_padding/2);
					img_padding = img_padding+30;
					img_padding = img_padding+"px";
					//$('#zoomImgSlideLayer').css({"height":"100%","margin-top":img_padding});
					$('#zoomImgSlideLayer').css({"height":w_h+"px"});
					$('#zoomImgSlideLayer img').css({"margin-top":img_padding});
					/* $('body,html').css({"background":"#000"}); */
				}
			}
			else
			{
				$('.slide-txt-info').text('1 / 1');
			}
			/* self logic end */
			return null;
		}

		// Create navigation
		if (!this.settings.disableNav) {
			var previousNav, nextNav;
			
			if (this.settings.previousNavSelector) {
				previousNav = document.querySelector(this.settings.previousNavSelector);
			} else {
				previousNav = document.createElement('a');
				sliderEl.appendChild(previousNav);
			}
			if (this.settings.nextNavSelector) {
				nextNav = document.querySelector(this.settings.nextNavSelector);
			} else {
				nextNav = document.createElement('a');
				sliderEl.appendChild(nextNav);
			}

			_addClass(previousNav, this.settings.classes.previousNav);
			_addClass(nextNav, this.settings.classes.nextNav);
			_addEvent(previousNav, 'click', function() {
				if (_hasClass(this._attributes.container, this.settings.classes.animating)) return false;
				this.stop();
				this.previousSlide();
			}.bind(this));
			_addEvent(nextNav, 'click', function() {
				if (_hasClass(this._attributes.container, this.settings.classes.animating)) return false;
				this.stop();
				this.nextSlide();
			}.bind(this));

			// Touch Navigation
			if (('ontouchstart' in window) || window.DocumentTouch && document instanceof DocumentTouch) {
				//console.log('Touch Navigation start');
				this.settings.effect = 'slide';
				previousNav.style.display = 'none';
				nextNav.style.display = 'none';
				_addClass(sliderEl, this.settings.classes.touchEnabled);
				_addEvent(sliderEl, 'touchstart', _touch.start.bind(this), false);
				_addEvent(sliderEl, 'touchmove', _touch.move.bind(this), false);
				_addEvent(sliderEl, 'touchend', _touch.end.bind(this), false);
			}

			// Keyboard Navigation
			/* default logic start */
			/*
			if (this.settings.keyboardNav) {
				_addEvent(document, 'keyup', function(e) {
					e = e || window.event;
					var button = (typeof e.which == 'number') ? e.which : e.keyCode;
					if (button == 37) {
						if (_hasClass(this._attributes.container, this.settings.classes.animating)) return false;
						this.stop();
						this.previousSlide();
					} else if (button == 39) {
						if (_hasClass(this._attributes.container, this.settings.classes.animating)) return false;
						this.stop();
						this.nextSlide();
					}
				}.bind(this));
			}
			*/
			/* default logic end */
		}
		
		/* self logic start */
		// Keyboard Navigation
		if (this.settings.keyboardNav) {
			_addEvent(document, 'keyup', function(e) {
				e = e || window.event;
				var button = (typeof e.which == 'number') ? e.which : e.keyCode;
				if (button == 37) {
					if (_hasClass(this._attributes.container, this.settings.classes.animating)) return false;
					this.stop();
					this.previousSlide();
				} else if (button == 39) {
					if (_hasClass(this._attributes.container, this.settings.classes.animating)) return false;
					this.stop();
					this.nextSlide();
				}
			}.bind(this));
		}
		/* self logic end */

		// Create internal attributes
		this._attributes = {
			container: sliderEl,
			slides: slides,
			previousSlide: typeof slides[slides.length - 1] !== 'undefined' ? slides[slides.length - 1] : slides[0],
			currentSlide: slides[0],
			nextSlide: typeof slides[1] !== 'undefined' ? slides[1] : slides[0],
			timerId: 0,
			origChildren: origChildren, // Used in destroy()
			aspectWidth: 0,
			aspectHeight: 0
		};

		// Set height
		if (_isInteger(this.settings.height)) {
			this._attributes.container.style.height = this.settings.height + 'px';
		} else {
			if (_isInteger(this.settings.initialHeight)) {
				this._attributes.container.style.height = this.settings.initialHeight + 'px';
			}

			// If aspect ratio parse and store
			if (this.settings.height.indexOf(':') > -1) {
				var aspectRatioParts = this.settings.height.split(':');
				if (aspectRatioParts.length == 2 && _isInteger(parseInt(aspectRatioParts[0], 10)) && _isInteger(parseInt(aspectRatioParts[1], 10))) {
					this._attributes.aspectWidth = parseInt(aspectRatioParts[0], 10);
					this._attributes.aspectHeight = parseInt(aspectRatioParts[1], 10);
				}
			}

			_addEvent(window, 'resize', function() {
				_setContainerHeight(this, false);
			}.bind(this));
		}
		
		// Add classes
		_addClass(sliderEl, this.settings.classes.container);
		_addClass(sliderEl, 'iis-effect-' + this.settings.effect);
		Array.prototype.forEach.call(this._attributes.slides, function(slide, i) {
			_addClass(slide, this.settings.classes.slide);
		}.bind(this));
		_addClass(this._attributes.previousSlide, this.settings.classes.previousSlide);
		_addClass(this._attributes.currentSlide, this.settings.classes.currentSlide);
		_addClass(this._attributes.nextSlide, this.settings.classes.nextSlide);

		// ARIA
		this._attributes.currentSlide.setAttribute('aria-hidden', 'false');

		// Load first image
		_loadImg(this._attributes.currentSlide, (function() {
			this.settings.onInit.apply(this);
			_setContainerHeight(this, false);
		}).bind(this));
		// Preload next images
		_loadImg(this._attributes.previousSlide);
		_loadImg(this._attributes.nextSlide);
	};

	Slider.prototype.get = function(attribute) {
		if (!this._attributes) return null;
		if (this._attributes.hasOwnProperty(attribute)) {
			return this._attributes[attribute];
		}
	};

	Slider.prototype.set = function(attribute, value) {
		if (!this._attributes) return null;
		return (this._attributes[attribute] = value);
	};

	Slider.prototype.start = function() {
		if (!this._attributes) return;
		this._attributes.timerId = setInterval(this.nextSlide.bind(this), this.settings.interval);
		this.settings.onStart.apply(this);

		// Stop if window blur
		window.onblur = function() {
			this.stop();
		}.bind(this);
	};

	Slider.prototype.stop = function() {
		if (!this._attributes) return;
		clearInterval(this._attributes.timerId);
		this._attributes.timerId = 0;
		this.settings.onStop.apply(this);
	};

	Slider.prototype.previousSlide = function() {
		
		this.settings.beforeChange.apply(this);
		_removeClass(this._attributes.previousSlide, this.settings.classes.previousSlide);
		_removeClass(this._attributes.currentSlide, this.settings.classes.currentSlide);
		_removeClass(this._attributes.nextSlide, this.settings.classes.nextSlide);
		this._attributes.currentSlide.setAttribute('aria-hidden', 'true');

		var slides = this._attributes.slides,
			index = slides.indexOf(this._attributes.currentSlide);
		this._attributes.nextSlide = this._attributes.currentSlide;
		this._attributes.previousSlide = slides[index - 2];
		this._attributes.currentSlide = slides[index - 1];
		if (typeof this._attributes.currentSlide === 'undefined' &&
			typeof this._attributes.previousSlide === 'undefined') {
			this._attributes.currentSlide = slides[slides.length - 1];
			this._attributes.previousSlide = slides[slides.length - 2];
			//var test_1 = slides.length-1;
			//var test_2 = slides.length-2;
			//console.log('previousSlide currentSlide='+test_1+' / previousSlide='+test_2);
		} else {
			if (typeof this._attributes.previousSlide === 'undefined') {
				this._attributes.previousSlide = slides[slides.length - 1];
				//var test_1 = slides.length-1;
				//console.log('previousSlide previousSlide='+test_1);
			}
		}
		// Preload next image
		_loadImg(this._attributes.previousSlide);

		_addClass(this._attributes.previousSlide, this.settings.classes.previousSlide);
		_addClass(this._attributes.currentSlide, this.settings.classes.currentSlide);
		_addClass(this._attributes.nextSlide, this.settings.classes.nextSlide);
		this._attributes.currentSlide.setAttribute('aria-hidden', 'false');

		_addClass(this._attributes.container, this.settings.classes.directionPrevious);
		_requestTimeout(function() {
			_removeClass(this._attributes.container, this.settings.classes.directionPrevious);
		}.bind(this), this.settings.transitionDuration);

		if (this.settings.transitionDuration) {
			_addClass(this._attributes.container, this.settings.classes.animating);
			_requestTimeout(function() {
				_removeClass(this._attributes.container, this.settings.classes.animating);
			}.bind(this), this.settings.transitionDuration);
		}
		
		/* self logic start */
		/*
var s_index = this._attributes.currentSlide.getAttribute('s-index');
		s_index = parseInt(s_index);		
		if(selfActLoc=='zoom' && is_parent_same_ch>0) parent.go_to_slide_assign_idx(s_index);
		var color_str = this._attributes.currentSlide.getAttribute('color-str');
		var txt_color_str = "";
		if(is_no_need_same_color_img<1 && color_str && typeof color_str!="undefined")
		{
			txt_color_str = ' &nbsp;'+color_str
		}
		var share_src = this._attributes.currentSlide.getAttribute('share-src');
		var share_bf_src = this._attributes.currentSlide.getAttribute('share-bf-src');
		if(share_src && share_bf_src && typeof share_src!="undefined" && typeof share_bf_src!="undefined")
		{
			if(typeof wx_e_imgUrl!="undefined" && typeof wx_e_bf_imgUrl!="undefined")
			{
				//console.log('reassign');
				wx_e_imgUrl = share_src;
				wx_e_bf_imgUrl = share_bf_src;
			}
			//console.log('previousSlide func share_src='+share_src+'\n share_bf_src='+share_bf_src+'\n wx_e_imgUrl='+wx_e_imgUrl+'\n wx_e_bf_imgUrl='+wx_e_bf_imgUrl);
		}
		if(selfActLoc=='zoom')
		{
			$('#zoomImgPopup .slide-txt-info', parent.document).html(s_index+' / '+slide_img_r_ct+txt_color_str);
			if(is_parent_same_ch>0)
			{
				$('#imgSlideLayer .slide-txt-info', parent.document).html(s_index+' / '+slide_img_r_ct+txt_color_str);
			}
		}
		else
		{
			//console.log('onsale-noti-icon-3 s_index='+s_index+' / is_onsale_icon='+is_onsale_icon);
			if(is_onsale_icon > 0)
			{
				if(s_index == 1)
				{
					$('.onsale-noti-str').css('display', 'none');
					$('.onsale-noti-icon').css('display', 'block');
				}
				else
				{
					$('.onsale-noti-str').css('display', 'none');
					$('.onsale-noti-icon').css('display', 'none');
				}
			}
			$('.slide-txt-info').html(s_index+' / '+slide_img_r_ct+txt_color_str);
		}
*/
		/* self logic end */

		_setContainerHeight(this);
		this.settings.afterChange.apply(this);
	};

	Slider.prototype.nextSlide = function() {
		this.settings.beforeChange.apply(this);
		_removeClass(this._attributes.previousSlide, this.settings.classes.previousSlide);
		_removeClass(this._attributes.currentSlide, this.settings.classes.currentSlide);
		_removeClass(this._attributes.nextSlide, this.settings.classes.nextSlide);
		this._attributes.currentSlide.setAttribute('aria-hidden', 'true');

		var slides = this._attributes.slides,
			index = slides.indexOf(this._attributes.currentSlide);
		this._attributes.previousSlide = this._attributes.currentSlide;
		this._attributes.currentSlide = slides[index + 1];
		this._attributes.nextSlide = slides[index + 2];
		if (typeof this._attributes.currentSlide === 'undefined' &&
			typeof this._attributes.nextSlide === 'undefined') {
			this._attributes.currentSlide = slides[0];
			this._attributes.nextSlide = slides[1];
		} else {
			if (typeof this._attributes.nextSlide === 'undefined') {
				this._attributes.nextSlide = slides[0];
			}
		}

		// Preload next image
		_loadImg(this._attributes.nextSlide);

		_addClass(this._attributes.previousSlide, this.settings.classes.previousSlide);
		_addClass(this._attributes.currentSlide, this.settings.classes.currentSlide);
		_addClass(this._attributes.nextSlide, this.settings.classes.nextSlide);
		this._attributes.currentSlide.setAttribute('aria-hidden', 'false');

		_addClass(this._attributes.container, this.settings.classes.directionNext);
		_requestTimeout(function() {
			_removeClass(this._attributes.container, this.settings.classes.directionNext);
		}.bind(this), this.settings.transitionDuration);

		if (this.settings.transitionDuration) {
			_addClass(this._attributes.container, this.settings.classes.animating);
			_requestTimeout(function() {
				_removeClass(this._attributes.container, this.settings.classes.animating);
			}.bind(this), this.settings.transitionDuration);
		}
		
		/* self logic start */
		/*
var s_index = this._attributes.currentSlide.getAttribute('s-index');
		s_index = parseInt(s_index);		
		if(selfActLoc=='zoom' && is_parent_same_ch>0) parent.go_to_slide_assign_idx(s_index);
		var color_str = this._attributes.currentSlide.getAttribute('color-str');
		var txt_color_str = "";
		if(is_no_need_same_color_img<1 && color_str && typeof color_str!="undefined")
		{
			txt_color_str = ' &nbsp;'+color_str
		}
		var share_src = this._attributes.currentSlide.getAttribute('share-src');
		var share_bf_src = this._attributes.currentSlide.getAttribute('share-bf-src');
		if(share_src && share_bf_src && typeof share_src!="undefined" && typeof share_bf_src!="undefined")
		{
			if(typeof wx_e_imgUrl!="undefined" && typeof wx_e_bf_imgUrl!="undefined")
			{
				//console.log('reassign');
				wx_e_imgUrl = share_src;
				wx_e_bf_imgUrl = share_bf_src;
			}
			//console.log('nextSlide func share_src='+share_src+'\n share_bf_src='+share_bf_src+'\n wx_e_imgUrl='+wx_e_imgUrl+'\n wx_e_bf_imgUrl='+wx_e_bf_imgUrl);
		}
		if(selfActLoc=='zoom')
		{
			$('#zoomImgPopup .slide-txt-info', parent.document).html(s_index+' / '+slide_img_r_ct+txt_color_str);
			if(is_parent_same_ch>0)
			{
				$('#imgSlideLayer .slide-txt-info', parent.document).html(s_index+' / '+slide_img_r_ct+txt_color_str);
			}
		}
		else
		{
			//console.log('onsale-noti-icon-4 s_index='+s_index+' / is_onsale_icon='+is_onsale_icon);
			if(is_onsale_icon > 0)
			{
				if(s_index == 1)
				{
					$('.onsale-noti-str').css('display', 'none');
					$('.onsale-noti-icon').css('display', 'block');
				}
				else
				{
					$('.onsale-noti-str').css('display', 'none');
					$('.onsale-noti-icon').css('display', 'none');
				}
			}
			$('.slide-txt-info').html(s_index+' / '+slide_img_r_ct+txt_color_str);
		}
*/
		/* self logic end */

		_setContainerHeight(this);
		this.settings.afterChange.apply(this);
	};

	Slider.prototype.gotoSlide = function(index) {
		this.settings.beforeChange.apply(this);
		this.stop();

		_removeClass(this._attributes.previousSlide, this.settings.classes.previousSlide);
		_removeClass(this._attributes.currentSlide, this.settings.classes.currentSlide);
		_removeClass(this._attributes.nextSlide, this.settings.classes.nextSlide);
		this._attributes.currentSlide.setAttribute('aria-hidden', 'true');

		index--; // Index should be 1-indexed
		var slides = this._attributes.slides,
			oldIndex = slides.indexOf(this._attributes.currentSlide);
		this._attributes.previousSlide = slides[index - 1];
		this._attributes.currentSlide = slides[index];
		this._attributes.nextSlide = slides[index + 1];
		
		if (typeof this._attributes.previousSlide === 'undefined') {
			this._attributes.previousSlide = slides[slides.length - 1];
		}
		if (typeof this._attributes.nextSlide === 'undefined') {
			this._attributes.nextSlide = slides[0];
			//console.log('nextSlide undefined');
		}

		// Load images
		_loadImg(this._attributes.previousSlide);
		_loadImg(this._attributes.currentSlide);
		_loadImg(this._attributes.nextSlide);

		_addClass(this._attributes.previousSlide, this.settings.classes.previousSlide);
		_addClass(this._attributes.currentSlide, this.settings.classes.currentSlide);
		_addClass(this._attributes.nextSlide, this.settings.classes.nextSlide);
		this._attributes.currentSlide.setAttribute('aria-hidden', 'false');

		//console.log('gotoSlide index='+index+' / oldIndex='+oldIndex+' / currentSlide idx='+slides.indexOf(this._attributes.currentSlide));	
		/* self logic start */
		/*
var s_index = this._attributes.currentSlide.getAttribute('s-index');
		s_index = parseInt(s_index);	
		var color_str = this._attributes.currentSlide.getAttribute('color-str');
		var txt_color_str = "";
		if(is_no_need_same_color_img<1 && color_str && typeof color_str!="undefined")
		{
			txt_color_str = ' &nbsp;'+color_str
		}
		var share_src = this._attributes.currentSlide.getAttribute('share-src');
		var share_bf_src = this._attributes.currentSlide.getAttribute('share-bf-src');
		if(share_src && share_bf_src && typeof share_src!="undefined" && typeof share_bf_src!="undefined")
		{
			if(typeof wx_e_imgUrl!="undefined" && typeof wx_e_bf_imgUrl!="undefined")
			{
				//console.log('reassign');
				wx_e_imgUrl = share_src;
				wx_e_bf_imgUrl = share_bf_src;
			}
			//console.log('gotoSlide func share_src='+share_src+'\n share_bf_src='+share_bf_src+'\n wx_e_imgUrl='+wx_e_imgUrl+'\n wx_e_bf_imgUrl='+wx_e_bf_imgUrl);
		}
		if(selfActLoc=='zoom')
		{
			$('#zoomImgPopup .slide-txt-info', parent.document).html(s_index+' / '+slide_img_r_ct+txt_color_str);
			if(is_parent_same_ch>0)
			{
				$('#imgSlideLayer .slide-txt-info', parent.document).html(s_index+' / '+slide_img_r_ct+txt_color_str);
			}
		}
		else
		{
			//console.log('onsale-noti-icon-5 s_index='+s_index+' / is_onsale_icon='+is_onsale_icon);
			if(is_onsale_icon > 0)
			{
				if(s_index == 1)
				{
					$('.onsale-noti-str').css('display', 'none');
					$('.onsale-noti-icon').css('display', 'block');
				}
				else
				{
					$('.onsale-noti-str').css('display', 'none');
					$('.onsale-noti-icon').css('display', 'none');
				}
			}
			$('.slide-txt-info').html(s_index+' / '+slide_img_r_ct+txt_color_str);
		}
*/
		/* self logic end */
			
		if (index < oldIndex) {
			_addClass(this._attributes.container, this.settings.classes.directionPrevious);
			_requestTimeout(function() {
				_removeClass(this._attributes.container, this.settings.classes.directionPrevious);
			}.bind(this), this.settings.transitionDuration);
		} else {
			_addClass(this._attributes.container, this.settings.classes.directionNext);
			_requestTimeout(function() {
				_removeClass(this._attributes.container, this.settings.classes.directionNext);
			}.bind(this), this.settings.transitionDuration);
		}

		if (this.settings.transitionDuration) {
			_addClass(this._attributes.container, this.settings.classes.animating);
			_requestTimeout(function() {
				_removeClass(this._attributes.container, this.settings.classes.animating);
			}.bind(this), this.settings.transitionDuration);
		}

		_setContainerHeight(this);
		this.settings.afterChange.apply(this);
		
	};

	Slider.prototype.destroy = function() {
		clearInterval(this._attributes.timerId);
		this._attributes.timerId = 0;

		this._attributes.container.innerHTML = '';
		Array.prototype.forEach.call(this._attributes.origChildren, function(child, i) {
			this._attributes.container.appendChild(child);
		}.bind(this));

		_removeClass(this._attributes.container, this.settings.classes.container);
		_removeClass(this._attributes.container, 'iis-effect-' + this.settings.effect);
		this._attributes.container.style.height = '';

		this.settings.onDestroy.apply(this);
	};

	return {
		_hasClass: _hasClass,
		_addClass: _addClass,
		_removeClass: _removeClass,
		Slider: Slider
	};

})();