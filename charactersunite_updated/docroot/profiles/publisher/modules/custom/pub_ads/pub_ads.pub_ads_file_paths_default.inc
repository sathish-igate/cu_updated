<?php
/**
 * @file
 * pub_ads.pub_ads_file_paths_default.inc
 */

/**
 * Implements hook_default_pub_ads_file_path().
 */
function pub_ads_default_pub_ads_file_path() {
  $export = array();

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'adcentric';
  $adpath->name = 'AdCentric';
  $adpath->path = 'AdCentric/adcentric.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html><body bgcolor=white>
<script language=javascript>
function pq(q) {
        if(q.length > 1) this.q = q.substring(1, q.length);
        else this.q = null;
        this.keyValuePairs = new Array();
        if(q) {
                for(var i=0; i < this.q.split("&").length; i++) {
                        this.keyValuePairs[i] = this.q.split("&")[i];
                }
        }
        this.getValue = function(s) {
                for(var j=0; j < this.keyValuePairs.length; j++) {
                        if(this.keyValuePairs[j].split("=")[0] == s)
                                return this.keyValuePairs[j].split("=")[1];
                }
                return -1;
        }
}
function qs(key){
        var page = new pq(document.location.search);
        return unescape(page.getValue(key));
}
var _c = qs(\'c\');
var r_number = Math.random();
document.writeln(\'<SCR\'+\'IPT language=\\\'JavaScript\\\' S\'+\'RC="http://media.adcentriconline.com/adcentric/tag/\'+_c+\'?ADCadcifr=1&number=\'+r_number+\'"></SCR\'+\'IPT>\');
</script>
</body></html>
';
  $export['adcentric'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'adconion';
  $adpath->name = 'Adconion';
  $adpath->path = 'adconion/ife.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html>
<head></head>
<body marginheight="0" marginwidth="0" style="margin: 0px;">
<script type="text/javascript">
(function() {

  function loadScript(url) {
    document.write(\'<s\' + \'cript type="text/javascript" src="\' + url
      + \'"></s\' + \'cript>\');
    }

    if ("https:" == document.location.protocol) {
      loadScript("https://cdns.amgdgt.com/base/js/v1/amgdgt-util.js");
      loadScript("https://cdns.amgdgt.com/base/js/v1/amgdgt-ife.js");
    } else {
      loadScript("http://cdn.amgdgt.com/base/js/v1/amgdgt-util.js");
      loadScript("http://cdn.amgdgt.com/base/js/v1/amgdgt-ife.js");
    }
})();
</script>
</html>';
  $export['adconion'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'adinterax';
  $adpath->name = 'AdInterax';
  $adpath->path = 'adinterax/adinterax.html';
  $adpath->file_type = 'html';
  $adpath->content = '<HTML>
<HEAD>
<SCRIPT>

// (c) 2004 adInterax, All Rights Reserved, http://adinterax.com
//
// !! DO NOT MODIFY THIS PAGE IN ANY WAY !!

var adxid=Math.random();
var k,v,l=location.href,l2,l3,i,p=new Array(),u,a=new Array(\'ad\',\'nest\',\'extra\');
if ((i=l.indexOf("?"))>0) {
    l2=l.substr(i+1)+\'&\';
    while ((i=l2.indexOf(\'&\'))>0) {
        l3=l2.substr(0,i);
        l2=l2.substr(i+1);
        if ((i=l3.indexOf(\'=\'))>0) {
            k=l3.substr(0,i);
            v=unescape(l3.substr(i+1));
            for(i=0;i<3;i++) if(k==a[i]) { p[i]=v;break }
            if(i>2)eval("var "+k+"=\'"+v+"\'");
        }
    }
}
u=\'http://\'+p[0]+\'/ad-iframe.js?\';
for (i=1;i<3;i++) if (p[i]) u+=a[i]+\'=\'+escape(p[i])+\'&\';

</SCRIPT>
</HEAD>
<BODY STYLE="margin:0px">
<SCRIPT>
 document.write(\'<SCR\'+\'IPT LANGUAGE="Javascript" SRC="\'+u+\'"></SCR\'+\'IPT>\')
</SCRIPT>
</BODY>
</HTML>';
  $export['adinterax'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'atlas';
  $adpath->name = 'Atlas';
  $adpath->path = 'atlas/atlas_rm.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html>
<head>
</head>
<body>
<script src=\'http://rmd.atdmt.com/tl/newIframeScript.js\'> </script>


</body>
</html>';
  $export['atlas'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'checkm8';
  $adpath->name = 'Checkm8';
  $adpath->path = 'checkm8/CM8IframeBuster.html';
  $adpath->file_type = 'html';
  $adpath->content = '<HTML><HEAD></HEAD><BODY>
  <SCRIPT LANGUAGE="JavaScript">
    for (;;) {
      try {
        parent.parent.document;
        break;
      }
      catch(e) {
        if (document.domain.split(".").length <= 2)
          break;
        document.domain = document.domain.substr(document.domain.indexOf(".") + 1);
      }
    }
  </SCRIPT>
  <SCRIPT LANGUAGE="JavaScript">
    var doc = parent.parent.document;
    if (! parent.parent.CM8IframeBusters)
      parent.parent.CM8IframeBusters = [];
    parent.parent.CM8IframeBusters.push(document.location.search.substr(1));
    var tag = doc.createElement(\'SCRIPT\');
    tag.src = ((document.location.protocol=="https:")?"https":"http") + "://" +
        document.location.search.replace(/.*&server=/, "").replace(/&.*/, "") +
        "/adam/cm8adam_iframe_buster_in.js";
    doc.body.insertBefore(tag, doc.body.firstChild);
  </SCRIPT>
</BODY></HTML>';
  $export['checkm8'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'comscore';
  $adpath->name = 'Comscore';
  $adpath->path = 'comscore/cs-arlframe.htm';
  $adpath->file_type = 'html';
  $adpath->content = '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
		<title>Iframe helper</title>
	</head>
	<body>
		<div id="debug"></div>
		<script>
			function getQueryStringParams(url) {
				var params = {};
				if (!url ) {
					return params;
				}

				var pairs = url.replace(/^[^\\?]+\\??/,\'\').split(/[;&]/);
				for (var i = 0; i < pairs.length; i++) {
					var keyVal = pairs[i].split(\'=\');
					if (!keyVal || keyVal.length != 2) continue;

					var key = decodeURIComponent(keyVal[0]);
					var val = decodeURIComponent(keyVal[1]);

					val = val.replace(/\\+/g, \' \');
					params[key] = val;
				}

				return params;
			}

			function setDomain() {
			var dom = document.domain;
				if (isTopAccessible()) {
					return;
				}
			while(dom.split(".").length > 2) {
				var newDomain = dom.substr(dom.indexOf(".") + 1);
				document.domain = newDomain;

					if (isTopAccessible()) {
						break;
					}

					dom = newDomain;
			}
			}

			function isTopAccessible() {
				try {
					top.document.getElementsByTagName(\'p\');
					return true;
				}
				catch (e) {
					return false;
				}
			}

			setDomain();
			var params = getQueryStringParams(document.location.toString());
			var url = params[\'nodeUrl\'] + \'?\';
			delete params[\'nodeUrl\'];
			for (var x in params) {
				url += x + \'=\' + params[x] + \'&\';
			}

			try {
				var script = top.document.createElement(\'script\');
				script.src = url;
				top.document.body.appendChild(script);
			}
			catch (e) {
			}
		</script>
	</body>
</html>
';
  $export['comscore'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'dart';
  $adpath->name = 'DART';
  $adpath->path = 'doubleclick/DARTIframe.html';
  $adpath->file_type = 'html';
  $adpath->content = '<HTML>
<HEAD>
</HEAD>
<BODY>
<SCRIPT language=JavaScript>
<!--
	function loadIFrameScript() {
		try {
			var mediaServer = "";
			var globalTemplateVersion = "";
			var searchString = document.location.search.substr(1);
			var parameters = searchString.split(\'&\');

			for(var i = 0; i < parameters.length; i++) {
				var keyValuePair = parameters[i].split(\'=\');
				var parameterName = keyValuePair[0];
				var parameterValue = keyValuePair[1];

				if(parameterName == "gtVersion")
					globalTemplateVersion = unescape(parameterValue);
				else if(parameterName == "mediaserver")
					mediaServer = unescape(parameterValue);
			}

			generateScriptBlock(mediaServer, globalTemplateVersion);
		}
		catch(e) {
		}
	}

	function generateScriptBlock(mediaServerUrl, gtVersion) {

		if(!isValid(gtVersion)) {
			reportError();
			return;
		}

		var mediaServerParts = mediaServerUrl.split("/");
		var host = mediaServerParts[2];
		var hostParts = host.split(".");

		if(hostParts.length > 4 || hostParts.length < 3) {
			reportError();
		return;
		}

		var subdomainOne = hostParts[0];
		if(!isValid(subdomainOne)) {
			reportError();
			return;
		}

		var subdomainTwo = (hostParts.length == 4) ? hostParts[1] : "";
		if(!isValid(subdomainTwo)) {
			reportError();
			return;
		}

		var subdomain = subdomainOne + ((subdomainTwo == "") ? "" : "." + subdomainTwo);

		var advertiserId = mediaServerParts[3];
		if(!isValid(advertiserId)) {
			reportError();
			return;
		}

		// Generate call to the script file on DoubleClick server.

		var publisherProtocol = window.location.protocol + "//";
		var iframeScriptFile = advertiserId + \'/DARTIFrame_\' + gtVersion + \'.js\';
		var urlStart = publisherProtocol + subdomain;
		//document.write(\'<scr\' + \'ipt src="\' + urlStart + ".doubleclick.net/" + iframeScriptFile + \'">\');
		//Wei: 7/15/2008
		document.write(\'<scr\' + \'ipt src="\' + urlStart + ".2mdn.net/" + iframeScriptFile + \'">\');
		document.write(\'</scr\'+ \'ipt>\');
	}

	// Validation routine for parameters passed on the URL.
	// The parameter should contain only word characters including underscore (limited to \'\\w\')
	// and should not exceed 15 characters in length.
	function isValid(stringValue) {
		var isValid = false;

		if(stringValue.length <= 15 && stringValue.search(new RegExp("[^A-Za-z0-9_]")) == -1)
			isValid = true;

		return isValid;
	}

	//Report error to the DoubleClick ad server.
	function reportError() {
		var publisherProtocol = window.location.protocol + "//";
		document.write(\' <img src="\' + publisherProtocol + \'ad.doubleclick.net/activity;badserve=1" style="visibility:hidden" width=1 height=1>\');
	}


	loadIFrameScript();

-->
</SCRIPT>
</BODY>
</HTML>
 ';
  $export['dart'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'eyeblaster';
  $adpath->name = 'Eyeblaster';
  $adpath->path = 'eyeblaster/addineyeV2.html';
  $adpath->file_type = 'html';
  $adpath->content = '<HTML>
<HEAD>
</HEAD>
<BODY style=margin:0;padding:0>
<script>
var strProtocol = document.location.protocol+"//";
var strAddInEyeSrc = "ds.serving-sys.com/BurstingScript/addineye.js";
if(strProtocol == "https://")
     strAddInEyeSrc = "secure-"+ strAddInEyeSrc;
strAddInEyeSrc = strProtocol + strAddInEyeSrc;
document.write("<scr"+"ipt src="+strAddInEyeSrc+"></scr"+"ipt>");
</script>
</BODY>
</HTML>';
  $export['eyeblaster'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'eyeblasters';
  $adpath->name = 'Eyeblaster Secure';
  $adpath->path = 'eyeblaster/addineyeV2-secure.html';
  $adpath->file_type = 'html';
  $adpath->content = '<HTML>
<HEAD>
</HEAD>
<BODY style=margin:0;padding:0>
<script>
var strProtocol = document.location.protocol+"//";
var strAddInEyeSrc = "ds.serving-sys.com/BurstingScript/addineye.js";
if(strProtocol == "https://")
     strAddInEyeSrc = "secure-"+ strAddInEyeSrc;
strAddInEyeSrc = strProtocol + strAddInEyeSrc;
document.write("<scr"+"ipt src="+strAddInEyeSrc+"></scr"+"ipt>");
</script>
</BODY>
</HTML>';
  $export['eyeblasters'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'eyengage';
  $adpath->name = 'Eyengage';
  $adpath->path = 'eyengage/eyengage.html';
  $adpath->file_type = 'html';
  $adpath->content = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</head>
<body style="margin:0;padding:0;">
<script type="text/javascript" src="http://cache.trafficmp.com/adv/javascript/bridge.js"></script>
</body>
</html><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</head>
<body style="margin:0;padding:0;">
<script type="text/javascript" src="http://cache.trafficmp.com/adv/javascript/bridge.js"></script>
</body>
</html>';
  $export['eyengage'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'eyereturn';
  $adpath->name = 'Eyereturn';
  $adpath->path = 'eyereturn/eyereturn.html';
  $adpath->file_type = 'html';
  $adpath->content = '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<body>
<script>
<!--
var er_qsStr = unescape(location.search.substring(1, location.search.length));
	if (er_qsStr.length > 0) {
		document.write (\'<scr\' + \'ipt language="JavaScript" src="http://voken.eyereturn.com/?\' + er_qsStr + \'"><\\/sc\' + \'ript>\');
	}
//-->
</script>
</body>
</html>';
  $export['eyereturn'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'eyewonder';
  $adpath->name = 'Eyewonder';
  $adpath->path = 'eyewonder/interim.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html><head><title>Ad</title></head><body><script type="text/javascript">var cdn="100125"; if(window.location.search.indexOf("/300125/")>0) cdn="300125"; document.writeln(\'<scr\'+\'ipt type="text/javascript" src="http://cdn.eyewonder.com/\'+cdn+\'/QA/_interim.js?ewbust=\'+new Date().getTime()+\'"></scr\'+\'ipt>\');</script></body></html>';
  $export['eyewonder'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'flashtalking';
  $adpath->name = 'Flashtalking';
  $adpath->path = 'flashtalking/ftlocal.html';
  $adpath->file_type = 'html';
  $adpath->content = '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html><head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
<script language="JavaScript">
document.domain=\'ivillage.com\';
var qs = new Querystring()
function Querystring()
{
	var querystring=location.search.substring(1,location.search.length);
	querystring = decodeURIComponent(querystring);
	var args = querystring.split(\'&\');
	for (var i=0;i<args.length;i++)
	{
		var pair = args[i].split(\'=\');
		if (pair.length > 1){
			for (var i2=2;i2<pair.length;i2++)
			{
				pair[1] += "=" + pair[i2];
			}
		}
		temp = unescape(pair[0]).split(\'+\');
		temp0 = temp.join(\' \');
		temp = unescape(pair[1]).split(\'+\');
		temp1 = temp.join(\' \');
		this[temp0]=temp1;
	}
	this.get=Querystring_get;
}
function Querystring_get(strKey,strDefault)
{
	var value=this[strKey];
	if (value==null){value=strDefault;}
	return value;
}

var parentpage = eval("parent.parent");

function loadftscript(){

	var ftscript02 = document.createElement("script");
	ftscript02.setAttribute("src",qs.get("ifsrc",""));
	ftscript02.id = "ftscript";

	document.body.appendChild(ftscript02);

}

function loadpage(){
	if (document.all){
		if (parentpage.document.readyState == \'complete\'){
			loadftscript();
		} else {
			setTimeout("loadpage()",150);
		}
	} else {
		loadftscript();
	}
}


</script>


</head>
<body onload="loadpage()">


<script id="ftscript" src=""></script></body></html>';
  $export['flashtalking'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'flite';
  $adpath->name = 'Flite';
  $adpath->path = 'flite/fif.html';
  $adpath->file_type = 'html';
  $adpath->content = '
<HTML>
<HEAD>
    <style type="text/css">
        #widgetbox_widget_div_0, body{
            margin:0px;
            padding:0px;
        }
    </style>
</HEAD>
<BODY onLoad="go()">
<SCRIPT type="text/javascript">

	function getQueryParameter(name, url){
		if(!url)url = window.location.href;
		var regexS = "[\\\\?&]"+name+"=([^&#]*)";
		var regex = new RegExp( regexS );
		var results = regex.exec( url );
		if( results == null ){
			return "";
		}else{
			return decodeURIComponent(results[1]);
		}
	}

    function buildScript(path) {
        var scriptSrc = "http://cdn.widgetserver.com/syndication/platform/InsertWidget/fif/default/" + path;
        var script = document.createElement("script");
        script.type = "text/javascript";
        script.src = scriptSrc;

        setTimeout(document.body.appendChild(script), 1);
	}

    function go(){
        var inFIFDisabled = getQueryParameter("f", location.href) == "false";
        var inFIF = !inFIFDisabled;
        var isAJAX = true;

        var p = getQueryParameter("p", location.href);
        if (p && p.length>0) {
            buildScript(p);
        }
    }

</SCRIPT>
</BODY>
</HTML>';
  $export['flite'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'icompass';
  $adpath->name = 'Icompass';
  $adpath->path = 'icompass/iFrameReleaseFile.html';
  $adpath->file_type = 'html';
  $adpath->content = '<?xml encoding="UTF-8" version="1.0" ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta content="text/html; encoding=UTF-8" http-equiv="content-type" />

    <script src="http://icompass.insightexpressai.com/iframe.js" type="text/javascript"></script>

</head>
<body>
</body>
</html>';
  $export['icompass'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'klipmart';
  $adpath->name = 'Klipmart';
  $adpath->path = 'klipmart/klipmart.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html>
<head>
<style>
BODY{
	background-color:transparent;
	margin-bottom:0;
	margin-left:0;
	margin-top:0;
	margin-right:0;
}
</style>
<script language="javascript" type="text/javascript" src="http://gfx.dvlabs.com/klipmart/tools/km_ss.js"></script>
</head>
<body>
</body>
</html>';
  $export['klipmart'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'mixpo';
  $adpath->name = 'Mixpo';
  $adpath->path = 'mixpo/framebust.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html><head><script type="text/javascript">
var subdomain = \'swf\';
var params = location.search.substring(1).split(\'&\');
for (var i=0; i<params.length; i++) {
	var pair = params[i].split(\'=\');
	if (pair.length == 2 && pair[0] == \'subdomain\') {
		subdomain = pair[1];
	}
}
document.write(\'<script type="text/javascript" src="//\' + subdomain + \'.mixpo.com/js/bust.js"><\\/script>\');
</script></head></html>';
  $export['mixpo'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'oggi';
  $adpath->name = 'Oggi';
  $adpath->path = 'oggi/oggiPlayerLoader.htm';
  $adpath->file_type = 'html';
  $adpath->content = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>Frame Booster</title>
    <meta http-equiv="CACHE-CONTROL" content="NO-CACHE" />
    <meta http-equiv="PRAGMA" content="NO-CACHE" />
    <meta http-equiv="EXPIRES" content="0" />
    <meta http-equiv="ROBOTS" content="NONE" />
</head>
<body>
    <!--Framebuster Version:2-->
    <script type="text/javascript" src="http://static-cdn-cf.oggifinogi.com/prod/Buster.js"></script>
</body>
</html>';
  $export['oggi'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'pictela';
  $adpath->name = 'Pictela';
  $adpath->path = 'pictela/pictela_buster.html';
  $adpath->file_type = 'html';
  $adpath->content = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="language" content="en" />
<title></title>
</head>
<body style="margin:0px; padding:0px">
<script language="JavaScript" type="text/javascript">


	var params = {};
	params.cb ="";
	var qs = location.search.substring(1, location.search.length);
	if (qs.length != 0){
	var args = qs.split(\'&\'); // parse out name/value pairs separated via &

// split out each name=value pair
		for (var i = 0; i < args.length; i++) {
			var pair = args[i].split(\'=\');
			var name = decodeURIComponent(pair.shift());

			var value = pair.join("=");

			params[name] = value;
		}
	}

  //site_id
  if(typeof(params[\'siteid\']) != "undefined") {
  var g_pct_siteid = unescape(params[\'siteid\']);
  }
  //impression_tracker

  if(typeof(params[\'impression\']) != "undefined") {
	var g_pct_impression = unescape(unescape(unescape(params[\'impression\'])));
  }
  //click tracker
  if(typeof(params[\'pct\']) != "undefined") {
		var g_pct_clicktracker = unescape(unescape(unescape(params[\'pct\'])));
  }
  var syncID = "72342";
  if(typeof(params[\'syncID\']) != "undefined") {
		var syncID = unescape(unescape(unescape(params[\'syncID\'])));
  }
  if(typeof(params[\'ptela_docdomain\']) != "undefined") {
		document.domain = unescape(unescape(unescape(params[\'ptela_docdomain\'])));
  }



  var inDapIF=true;
document.write( \'<scr\' + \'ipt type="text/javascript" src="http://www.pictela.net/client/jsembed/id/\'+syncID+\'.js\'+document.location.search  +\'"></scr\'+\'ipt>\');
</script>
</body>
</html> ';
  $export['pictela'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'pointroll';
  $adpath->name = 'Pointroll';
  $adpath->path = 'pointroll/pointrollads.htm';
  $adpath->file_type = 'html';
  $adpath->content = '<script type="text/javascript" src="http://psf.pointroll.com/pointroll/script/psf.js"></script>';
  $export['pointroll'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'rovion';
  $adpath->name = 'Rovion';
  $adpath->path = 'rovion/Rovion_iframebust.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html>
<head>
<title>Rovion iFrame Buster</title>
<script type="text/javascript">
if(document.URL.split("rovioniframetopdomain=")[1] != ""){
	document.domain = document.URL.split("rovioniframetopdomain=")[1];
}
</script>
</head>
<body style="margin:0px;padding:0px;">
<script type="text/javascript">
/* COPYRIGHT 2001-<?=date("Y");?> ROVION, INC. (WWW.ROVION.COM) ALL RIGHTS RESERVED */
var inDapIF=true;
document.write(\'<scr\'+\'ipt type="text/javascript" src="\'+unescape(document.URL.split("&rovioniframetopdomain")[0].split("rovioniframeadurl=")[1])+\'"></scr\'+\'ipt>\');
</script>
</body>
</html>';
  $export['rovion'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'safecount';
  $adpath->name = 'Safecount';
  $adpath->path = 'safecount/getfile.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html>
<head></head>
<body style=margin:0;padding:0>
<script language="javascript">
// Get the parameters from the IFrame
var strSearch = document.location.search;
// Find a parameter called \'sub\'.  This holds the name of a server at QuestionMarket where the rest of the code is stored.
var subPos = strSearch.indexOf("sub");
// Pull this parameter out where we can use it.
var strHTML = unescape(strSearch.substr(subPos+4, strSearch.indexOf("&")-subPos-4));
// Insert a script from the indicated server into the containing page.  Pass the parameters to this script.
self.document.write(\'<scr\'+\'ipt language="javascript" src="http://\'+strHTML+\'.questionmarket.com/adscgen/dynamiclink.js.php\'+strSearch+\'"></scr\'+\'ipt>\');
</script>
</body>
</html>';
  $export['safecount'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'smartadserver';
  $adpath->name = 'Smartadserver';
  $adpath->path = 'smartadserver/smartadserver.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html>
<head><title>SmartAdserver IFrame Popout</title></head>
<body style="padding:0; margin:0">
<script src="http://www.smartadserver.com/iframeout/iframeout.js"></script>
</body>
</html>';
  $export['smartadserver'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'unicast';
  $adpath->name = 'Unicast';
  $adpath->path = 'unicast/unicastIFd.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html><head></head><body leftmargin=0 topmargin=0 marginwidth=0 marginheight=0><script language="javascript">s=unescape(document.location.search.substring(1));p=s.toLowerCase().indexOf("script")==-1?s.split(\'&\'):"";bgc="";scv="v05";scf="vwptifd202.js";if(p.length>0){if(p[0].indexOf("/")!=-1){scv="V1.8";}else if(p[0].indexOf("Ver")==0){scv="V"+p[0].substring(4,8);scf="ifd.js";for(var i=0;i<p.length;i++)   {var q=p[i].split("=");if(q&&q.length==2){if(q[0]=="Bgc"&&q[1].length==6)bgc="#"+q[1];}}}}      if(bgc!="")document.body.bgColor=bgc;var str="<scr"+"ipt language=\'javascript\' src=\'http://creativeby1.unicast.com/script/"+scv+"/"+scf+"\'></scr"+"ipt>";document.write(str);</script></body></html>';
  $export['unicast'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'videoegg';
  $adpath->name = 'Videoegg';
  $adpath->path = 'videoegg/videoegg.htm';
  $adpath->file_type = 'html';
  $adpath->content = '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML><HEAD>
<META http-equiv=Content-Type content="text/html; charset=windows-1252">
<META content="MSHTML 6.00.6000.16981" name=GENERATOR></HEAD>
<BODY>
<SCRIPT>
var config = {};
var am;
var hash = window.location.hash;
if (hash != null) {
    var str = unescape(unescape(hash));
	str = str.substring(2);
    str = str.substring(0, str.length - 2);
	str = str.replace(/[\'"]/g,\'\');

    var values = str.split(",");
    var l = values.length;
    for(var i = 0; i < l; i++) {
        var kvp = values[i].split(":");
        config[kvp[0]] = kvp.splice(1, kvp.length-1).join("");

        if(config[kvp[0]].substr(0,4) == "http") {
            config[kvp[0]] = config[kvp[0]].substr(0, 4) + \':\' + config[kvp[0]].substr(4, config[kvp[0]].length);
        }
    }
}

var EAP_VERSION = config.ev;

document.write(\'<script type="text/javascript" src="http://core.videoegg.com/eap/\' + EAP_VERSION + \'/html/js/iframe_ad.js"><\\/script>\');
</SCRIPT>

<DIV id=ad style="LEFT: 0px; POSITION: absolute; TOP: 0px"></DIV></BODY></HTML>';
  $export['videoegg'] = $adpath;

  $adpath = new stdClass();
  $adpath->disabled = FALSE; /* Edit this to true to make a default adpath disabled initially */
  $adpath->api_version = 1;
  $adpath->machine_name = 'viewpoint';
  $adpath->name = 'Viewpoint';
  $adpath->path = 'viewpoint/viewpoint.html';
  $adpath->file_type = 'html';
  $adpath->content = '<html><head></head><body leftmargin=0 topmargin=0 marginwidth=0 marginheight=0>
<script language=\'javascript\' src="http://creativeby.viewpoint.com/script/v05/vwptifd202.js">
</script>
</body></html>';
  $export['viewpoint'] = $adpath;

  return $export;
}
