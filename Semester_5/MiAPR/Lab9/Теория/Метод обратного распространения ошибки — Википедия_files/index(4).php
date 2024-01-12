/** Sort iw-links according to a preference table ****************************************************** 
 *
 *  First revision was imported from http://no.wikipedia.org/wiki/MediaWiki:Interwiki-links.js
 *  Original description [[:no:Wikipedia:Sortering av interwiki-lenker]]
 *
 */
//<nowiki>
 
var wgDebugIWlang;
var wgUseUserlanguage;
var wgLangPrefs;
var wgAddLangHints;
var wgLangNames;

(function($, mw, undefined) {
 
'use strict';

// Guard against multiple inclusions
if (typeof (window.InterwikiLinks) === 'object') return;  

var IWL,
	conf = mw.config.get([
		'wgContentLanguage',
		'wgUserLanguage',
		'wgUserName'
	]);
	
IWL = window.InterwikiLinks = {
	langLinks : {}
	/**
	** Runs before $(document).ready() and before translation is available
	** (important event-binders should be attached as fast as possible)
	**/
	, preinstall: 
		function () 
		{
			mw.util.addCSS('.iw-focus {font-weight: bold} .iw-babel {font-style: italic}');
			
			var defaultLangPrefs = [];
			// make sure we in fact has a array
			if (typeof wgLangPrefs == 'undefined') 
				wgLangPrefs = [];
			wgLangPrefs.push(conf.wgUserLanguage);
			// choose and adjust lists for prefered languages
			if (conf.wgUserName) {
				wgLangPrefs = wgLangPrefs;
			}
			else {
				wgLangPrefs = defaultLangPrefs;
			}
			for (var i=0; i < wgLangPrefs.length; i++) {
				wgLangPrefs[wgLangPrefs[i]] = 1;
				IWL.langLinks[wgLangPrefs[i]] = 1;
			}
		}
    , install : 
		function () 
		{
			// get data structures for nameing and sorting of languages
			// this will block any languages that isn't defined
			
			if (typeof wgLangNames != 'undefined' && typeof conf.wgUserLanguage != 'undefined' && typeof wgLangNames[conf.wgUserLanguage] == 'object') {
				// reorganize wgLangNames so we can use it for sorting
				IWL.langNames = {};
				var j = 0;
				for (var lang in wgLangNames[conf.wgUserLanguage]) {
					IWL.langNames[lang] = [ wgLangNames[conf.wgUserLanguage][lang], j ];
					j++;
				}
				// if we don't have anything from wgLangNames we give up
				if (!j) 
					return;
			} else {
				return;
			}
			// wait for document.readyState
			$(function() {
				// Trigger a jQuery event for other scripts that like to know
				// when this script has loaded all translations and is ready to install
				$(document).triggerHandler('scriptLoaded', ['InterwikiLinks']);				
				IWL.start();
			});
		}
	, sort : 
		function(a,b) 
		{
			try {
				return  IWL.langNames[ a.className.replace(/^.*?interwiki-/, '').replace(/\s.*$/, '') ][ 1 ] - 
						IWL.langNames[ b.className.replace(/^.*?interwiki-/, '').replace(/\s.*$/, '') ][ 1 ];
			}
			catch (e) {
				/* just skip this if its happens to fail, but then the link might be placed a bit random */
			}
		}
	, start :
		function () 
		{
			// locate iw-links, and the container
			var container = document.getElementById("p-lang");
			if (!container) 
				return;
			var ul = container.getElementsByTagName("ul");
			if (!ul) 
				return;
			if (ul.length != 1) 
				return;
			ul = ul[0];
			var c = container.getElementsByTagName("li");
			if (!c) 
				return;
		 
			// loop over the iw-links, translate names and
			// separate those we know how to sort from the rest
			// and add babel links
			var childs = [];
			var keeps = [];
			var adds = [];
			for (var i=0; i < c.length;i++) {
				if (typeof IWL.langNames != 'undefined') {
					if (c[ i ].className == "wbc-editpage") {
						adds.push(c[ i ]);
						continue;
					}
					var s = c[ i ].className;
					if (0>s.indexOf('interwiki-')) 
						continue;
					s = s.replace(/^.*?interwiki-/, '').replace(/\s.*$/, '');
					var a = c[ i ].getElementsByTagName("a");
		 
					// localize language names
					try {
						if ( typeof wgUseUserLanguage != 'undefined' && wgUseUserLanguage ) {
							if ( typeof IWL.langNames[ s ] != 'undefined'
								&& typeof IWL.langNames[ s ][ 0 ] == 'string' ) {
								if (a.length){
									a[0].innerHTML = IWL.langNames[ s ][ 0 ];
									a[0].lang = 'ru';
								}  
							}
						}
					}
					catch (e) { /* just skip this */ }
					// add hints for language names
					try {
						if ( typeof wgAddLangHints != 'undefined' && wgAddLangHints ) {
							if ( typeof IWL.langNames[ s ] != 'undefined'
								&& typeof IWL.langNames[ s ][ 0 ] == 'string' ) {
								a[0].setAttribute( 'title', this.langNames[ s ][ 0 ] + ' — ' + decodeURIComponent(a[0].getAttribute('href').replace(/^.*?\/wiki\/(.*)$/, '$1')).replace(/_/g, ' '));
							}
						}
					}            
					catch (e) { /* just skip this */ }
					// check if we have any odd link}
					try {
						if ( typeof wgUseUserLanguage != 'undefined' && wgUseUserLanguage
							&& typeof IWL.langNames[ s ] != 'undefined'
							&& typeof this.langNames[ s ][ 1 ] == 'number' ) {
							childs.push(c[ i ]);
						}
						else {
							adds.push(c[ i ]);
						}
					}
					catch (e) { /* just skip this */ }
				}
				else {
					childs.push(c[ i ]);
				}
			}
			// sort the childs according to definitions used by sortIWlinks
			if ( typeof wgUseUserLanguage != 'undefined' && wgUseUserLanguage) {
				childs = childs.sort(this.sort);
			}
			// reinsert those we didn't know how to sort into the list of children
			for (i=0; i<adds.length ;i++) {
				childs.push(adds[i]);
			}
			// move one block to the top
			try {
				// separate out those that shall be moved to the top
				for (i=0; i < childs.length; i++) {
					// the following test fails if there are several classes for the actual child
					var link = IWL.langLinks[ childs[i].className.replace(/^.*?interwiki-/, '').replace(/\s.*$/, '') ];
					if ( typeof link != 'undefined' && link) {
						keeps.push(childs[i]);
					}
				}
				// reorganize the list of children
				var n = childs.length;
				for (i=childs.length-1; i >= 0; i--) {
					link = IWL.langLinks[ childs[i].className.replace(/^.*?interwiki-/, '').replace(/\s.*$/, '') ];
					if ( typeof link != 'undefined'	&& link ) {
						childs[i].className += ' iw-focus';
					}
					else {
						keeps[--n] = childs[i];
					}
				}
			}
			catch (e) { /* just skip this */ }
			// remove all existing children and reinsert from our own list
			if (keeps.length) {
				var child;
				while ((child = ul.firstChild) !== null) {
					ul.removeChild(child);
				}
				for (i=0;i<keeps.length;i++) {
					ul.appendChild(keeps[i]);
				}
			}
		}	
	};
	
	if (mw.user.options.get('uls-compact-links') != "0") return; // don't work together
	if ( typeof wgDebugIWlang != 'undefined' && wgDebugIWlang ) return; // bail out for debugging
	
	IWL.preinstall();
	var allowedLanguages = { 'nn' : true, 'no' : true, 'ru' : true };
	if ( conf.wgUserName === null ? conf.wgUserLanguage != conf.wgContentLanguage : true ) {
		if ( conf.wgUserLanguage in allowedLanguages ) {
			// load script for wgLangNames
			$.ajax({
				url: mw.util.wikiScript(),
				dataType: 'script',
				data: {
					title: 'MediaWiki:User-lang-' + conf.wgUserLanguage + '.js',
					action: 'raw',
					ctype: 'text/javascript',
					// Allow caching for 28 days
					maxage: 2419200,
					smaxage: 2419200
				},
				cache: true,
				success: IWL.install,
				error: IWL.install
				});			
		}
	}
}(jQuery, mediaWiki));
// </nowiki>