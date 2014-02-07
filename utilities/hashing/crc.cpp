



<!DOCTYPE html>
<html>
<head>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link rel="icon" type="image/vnd.microsoft.icon" href="https://ssl.gstatic.com/codesite/ph/images/phosting.ico">
 
 
 <script type="text/javascript">
 
 
 
 
 var codesite_token = "EDu_oR3WPXBU5nElWWso8i2GYY4:1390098706435";
 
 
 var CS_env = {"projectName": "smhasher", "loggedInUserEmail": "alanparsonsproject28@gmail.com", "token": "EDu_oR3WPXBU5nElWWso8i2GYY4:1390098706435", "projectHomeUrl": "/p/smhasher", "profileUrl": "/u/109814223914636253922/", "assetVersionPath": "https://ssl.gstatic.com/codesite/ph/11104804043454007890", "assetHostPath": "https://ssl.gstatic.com/codesite/ph", "domainName": null, "relativeBaseUrl": ""};
 var _gaq = _gaq || [];
 _gaq.push(
 ['siteTracker._setAccount', 'UA-18071-1'],
 ['siteTracker._trackPageview']);
 
 _gaq.push(
 ['projectTracker._setAccount', 'UA-19521294-1'],
 ['projectTracker._trackPageview']);
 
 (function() {
 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
 (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(ga);
 })();
 
 </script>
 
 
 <title>crc.cpp - 
 smhasher -
 
 
 Test your hash functions. - Google Project Hosting
 </title>
 <link type="text/css" rel="stylesheet" href="https://ssl.gstatic.com/codesite/ph/11104804043454007890/css/core.css">
 
 <link type="text/css" rel="stylesheet" href="https://ssl.gstatic.com/codesite/ph/11104804043454007890/css/ph_detail.css" >
 
 
 <link type="text/css" rel="stylesheet" href="https://ssl.gstatic.com/codesite/ph/11104804043454007890/css/d_sb.css" >
 
 
 
<!--[if IE]>
 <link type="text/css" rel="stylesheet" href="https://ssl.gstatic.com/codesite/ph/11104804043454007890/css/d_ie.css" >
<![endif]-->
 <style type="text/css">
 .menuIcon.off { background: no-repeat url(https://ssl.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -42px }
 .menuIcon.on { background: no-repeat url(https://ssl.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -28px }
 .menuIcon.down { background: no-repeat url(https://ssl.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 0; }
 
 
 
  tr.inline_comment {
 background: #fff;
 vertical-align: top;
 }
 div.draft, div.published {
 padding: .3em;
 border: 1px solid #999; 
 margin-bottom: .1em;
 font-family: arial, sans-serif;
 max-width: 60em;
 }
 div.draft {
 background: #ffa;
 } 
 div.published {
 background: #e5ecf9;
 }
 div.published .body, div.draft .body {
 padding: .5em .1em .1em .1em;
 max-width: 60em;
 white-space: pre-wrap;
 white-space: -moz-pre-wrap;
 white-space: -pre-wrap;
 white-space: -o-pre-wrap;
 word-wrap: break-word;
 font-size: 1em;
 }
 div.draft .actions {
 margin-left: 1em;
 font-size: 90%;
 }
 div.draft form {
 padding: .5em .5em .5em 0;
 }
 div.draft textarea, div.published textarea {
 width: 95%;
 height: 10em;
 font-family: arial, sans-serif;
 margin-bottom: .5em;
 }

 
 .nocursor, .nocursor td, .cursor_hidden, .cursor_hidden td {
 background-color: white;
 height: 2px;
 }
 .cursor, .cursor td {
 background-color: darkblue;
 height: 2px;
 display: '';
 }
 
 
.list {
 border: 1px solid white;
 border-bottom: 0;
}

 
 </style>
</head>
<body class="t4">
<script type="text/javascript">
 window.___gcfg = {lang: 'en'};
 (function() 
 {var po = document.createElement("script");
 po.type = "text/javascript"; po.async = true;po.src = "https://apis.google.com/js/plusone.js";
 var s = document.getElementsByTagName("script")[0];
 s.parentNode.insertBefore(po, s);
 })();
</script>
<div class="headbg">

 <div id="gaia">
 

 <span>
 
 
 
 <a href="#" id="multilogin-dropdown" onclick="return false;"
 ><u><b>alanparsonsproject28@gmail.com</b></u> <small>&#9660;</small></a>
 
 
 | <a href="/u/109814223914636253922/" id="projects-dropdown" onclick="return false;"
 ><u>My favorites</u> <small>&#9660;</small></a>
 | <a href="/u/109814223914636253922/" onclick="_CS_click('/gb/ph/profile');"
 title="Profile, Updates, and Settings"
 ><u>Profile</u></a>
 | <a href="https://www.google.com/accounts/Logout?continue=https%3A%2F%2Fcode.google.com%2Fp%2Fsmhasher%2Fsource%2Fbrowse%2Ftrunk%2Fcrc.cpp" 
 onclick="_CS_click('/gb/ph/signout');"
 ><u>Sign out</u></a>
 
 </span>

 </div>

 <div class="gbh" style="left: 0pt;"></div>
 <div class="gbh" style="right: 0pt;"></div>
 
 
 <div style="height: 1px"></div>
<!--[if lte IE 7]>
<div style="text-align:center;">
Your version of Internet Explorer is not supported. Try a browser that
contributes to open source, such as <a href="http://www.firefox.com">Firefox</a>,
<a href="http://www.google.com/chrome">Google Chrome</a>, or
<a href="http://code.google.com/chrome/chromeframe/">Google Chrome Frame</a>.
</div>
<![endif]-->



 <table style="padding:0px; margin: 0px 0px 10px 0px; width:100%" cellpadding="0" cellspacing="0"
 itemscope itemtype="http://schema.org/CreativeWork">
 <tr style="height: 58px;">
 
 
 
 <td id="plogo">
 <link itemprop="url" href="/p/smhasher">
 <a href="/p/smhasher/">
 
 
 <img src="/p/smhasher/logo?cct=1367603841"
 alt="Logo" itemprop="image">
 
 </a>
 </td>
 
 <td style="padding-left: 0.5em">
 
 <div id="pname">
 <a href="/p/smhasher/"><span itemprop="name">smhasher</span></a>
 </div>
 
 <div id="psum">
 <a id="project_summary_link"
 href="/p/smhasher/"><span itemprop="description">Test your hash functions.</span></a>
 
 </div>
 
 
 </td>
 <td style="white-space:nowrap;text-align:right; vertical-align:bottom;">
 
 <form action="/hosting/search">
 <input size="30" name="q" value="" type="text">
 
 <input type="submit" name="projectsearch" value="Search projects" >
 </form>
 
 </tr>
 </table>

</div>

 
<div id="mt" class="gtb"> 
 <a href="/p/smhasher/" class="tab ">Project&nbsp;Home</a>
 
 
 
 
 
 
 <a href="/p/smhasher/w/list" class="tab ">Wiki</a>
 
 
 
 
 
 <a href="/p/smhasher/issues/list"
 class="tab ">Issues</a>
 
 
 
 
 
 <a href="/p/smhasher/source/checkout"
 class="tab active">Source</a>
 
 
 
 
 
 
 
 
 <div class=gtbc></div>
</div>
<table cellspacing="0" cellpadding="0" width="100%" align="center" border="0" class="st">
 <tr>
 
 
 
 
 
 
 <td class="subt">
 <div class="st2">
 <div class="isf">
 
 


 <span class="inst1"><a href="/p/smhasher/source/checkout">Checkout</a></span> &nbsp;
 <span class="inst2"><a href="/p/smhasher/source/browse/">Browse</a></span> &nbsp;
 <span class="inst3"><a href="/p/smhasher/source/list">Changes</a></span> &nbsp;
 
 
 
 
 
 
 
 </form>
 <script type="text/javascript">
 
 function codesearchQuery(form) {
 var query = document.getElementById('q').value;
 if (query) { form.action += '%20' + query; }
 }
 </script>
 </div>
</div>

 </td>
 
 
 
 <td align="right" valign="top" class="bevel-right"></td>
 </tr>
</table>


<script type="text/javascript">
 var cancelBubble = false;
 function _go(url) { document.location = url; }
</script>
<div id="maincol"
 
>

 




<div class="expand">
<div id="colcontrol">
<style type="text/css">
 #file_flipper { white-space: nowrap; padding-right: 2em; }
 #file_flipper.hidden { display: none; }
 #file_flipper .pagelink { color: #0000CC; text-decoration: underline; }
 #file_flipper #visiblefiles { padding-left: 0.5em; padding-right: 0.5em; }
</style>
<table id="nav_and_rev" class="list"
 cellpadding="0" cellspacing="0" width="100%">
 <tr>
 
 <td nowrap="nowrap" class="src_crumbs src_nav" width="33%">
 <strong class="src_nav">Source path:&nbsp;</strong>
 <span id="crumb_root">
 
 <a href="/p/smhasher/source/browse/">svn</a>/&nbsp;</span>
 <span id="crumb_links" class="ifClosed"><a href="/p/smhasher/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span>crc.cpp</span>
 
 


 </td>
 
 
 <td nowrap="nowrap" width="33%" align="center">
 <a href="/p/smhasher/source/browse/trunk/crc.cpp?edit=1"
 ><img src="https://ssl.gstatic.com/codesite/ph/images/pencil-y14.png"
 class="edit_icon">Edit file</a>
 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper">
 <ul class="leftside">
 
 <li><a href="/p/smhasher/source/browse/trunk/crc.cpp?r=90" title="Previous">&lsaquo;r90</a></li>
 
 </ul>
 </td>
 
 <td class="flipper"><b>r151</b></td>
 
 </tr></table>
 </td> 
 </tr>
</table>

<div class="fc">
 
 
 
<style type="text/css">
.undermouse span {
 background-image: url(https://ssl.gstatic.com/codesite/ph/images/comments.gif); }
</style>
<table class="opened" id="review_comment_area"
><tr>
<td id="nums">
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
<pre><table width="100%" id="nums_table_0"><tr id="gr_svn151_1"

><td id="1"><a href="#1">1</a></td></tr
><tr id="gr_svn151_2"

><td id="2"><a href="#2">2</a></td></tr
><tr id="gr_svn151_3"

><td id="3"><a href="#3">3</a></td></tr
><tr id="gr_svn151_4"

><td id="4"><a href="#4">4</a></td></tr
><tr id="gr_svn151_5"

><td id="5"><a href="#5">5</a></td></tr
><tr id="gr_svn151_6"

><td id="6"><a href="#6">6</a></td></tr
><tr id="gr_svn151_7"

><td id="7"><a href="#7">7</a></td></tr
><tr id="gr_svn151_8"

><td id="8"><a href="#8">8</a></td></tr
><tr id="gr_svn151_9"

><td id="9"><a href="#9">9</a></td></tr
><tr id="gr_svn151_10"

><td id="10"><a href="#10">10</a></td></tr
><tr id="gr_svn151_11"

><td id="11"><a href="#11">11</a></td></tr
><tr id="gr_svn151_12"

><td id="12"><a href="#12">12</a></td></tr
><tr id="gr_svn151_13"

><td id="13"><a href="#13">13</a></td></tr
><tr id="gr_svn151_14"

><td id="14"><a href="#14">14</a></td></tr
><tr id="gr_svn151_15"

><td id="15"><a href="#15">15</a></td></tr
><tr id="gr_svn151_16"

><td id="16"><a href="#16">16</a></td></tr
><tr id="gr_svn151_17"

><td id="17"><a href="#17">17</a></td></tr
><tr id="gr_svn151_18"

><td id="18"><a href="#18">18</a></td></tr
><tr id="gr_svn151_19"

><td id="19"><a href="#19">19</a></td></tr
><tr id="gr_svn151_20"

><td id="20"><a href="#20">20</a></td></tr
><tr id="gr_svn151_21"

><td id="21"><a href="#21">21</a></td></tr
><tr id="gr_svn151_22"

><td id="22"><a href="#22">22</a></td></tr
><tr id="gr_svn151_23"

><td id="23"><a href="#23">23</a></td></tr
><tr id="gr_svn151_24"

><td id="24"><a href="#24">24</a></td></tr
><tr id="gr_svn151_25"

><td id="25"><a href="#25">25</a></td></tr
><tr id="gr_svn151_26"

><td id="26"><a href="#26">26</a></td></tr
><tr id="gr_svn151_27"

><td id="27"><a href="#27">27</a></td></tr
><tr id="gr_svn151_28"

><td id="28"><a href="#28">28</a></td></tr
><tr id="gr_svn151_29"

><td id="29"><a href="#29">29</a></td></tr
><tr id="gr_svn151_30"

><td id="30"><a href="#30">30</a></td></tr
><tr id="gr_svn151_31"

><td id="31"><a href="#31">31</a></td></tr
><tr id="gr_svn151_32"

><td id="32"><a href="#32">32</a></td></tr
><tr id="gr_svn151_33"

><td id="33"><a href="#33">33</a></td></tr
><tr id="gr_svn151_34"

><td id="34"><a href="#34">34</a></td></tr
><tr id="gr_svn151_35"

><td id="35"><a href="#35">35</a></td></tr
><tr id="gr_svn151_36"

><td id="36"><a href="#36">36</a></td></tr
><tr id="gr_svn151_37"

><td id="37"><a href="#37">37</a></td></tr
><tr id="gr_svn151_38"

><td id="38"><a href="#38">38</a></td></tr
><tr id="gr_svn151_39"

><td id="39"><a href="#39">39</a></td></tr
><tr id="gr_svn151_40"

><td id="40"><a href="#40">40</a></td></tr
><tr id="gr_svn151_41"

><td id="41"><a href="#41">41</a></td></tr
><tr id="gr_svn151_42"

><td id="42"><a href="#42">42</a></td></tr
><tr id="gr_svn151_43"

><td id="43"><a href="#43">43</a></td></tr
><tr id="gr_svn151_44"

><td id="44"><a href="#44">44</a></td></tr
><tr id="gr_svn151_45"

><td id="45"><a href="#45">45</a></td></tr
><tr id="gr_svn151_46"

><td id="46"><a href="#46">46</a></td></tr
><tr id="gr_svn151_47"

><td id="47"><a href="#47">47</a></td></tr
><tr id="gr_svn151_48"

><td id="48"><a href="#48">48</a></td></tr
><tr id="gr_svn151_49"

><td id="49"><a href="#49">49</a></td></tr
><tr id="gr_svn151_50"

><td id="50"><a href="#50">50</a></td></tr
><tr id="gr_svn151_51"

><td id="51"><a href="#51">51</a></td></tr
><tr id="gr_svn151_52"

><td id="52"><a href="#52">52</a></td></tr
><tr id="gr_svn151_53"

><td id="53"><a href="#53">53</a></td></tr
><tr id="gr_svn151_54"

><td id="54"><a href="#54">54</a></td></tr
><tr id="gr_svn151_55"

><td id="55"><a href="#55">55</a></td></tr
><tr id="gr_svn151_56"

><td id="56"><a href="#56">56</a></td></tr
><tr id="gr_svn151_57"

><td id="57"><a href="#57">57</a></td></tr
><tr id="gr_svn151_58"

><td id="58"><a href="#58">58</a></td></tr
><tr id="gr_svn151_59"

><td id="59"><a href="#59">59</a></td></tr
><tr id="gr_svn151_60"

><td id="60"><a href="#60">60</a></td></tr
><tr id="gr_svn151_61"

><td id="61"><a href="#61">61</a></td></tr
><tr id="gr_svn151_62"

><td id="62"><a href="#62">62</a></td></tr
><tr id="gr_svn151_63"

><td id="63"><a href="#63">63</a></td></tr
><tr id="gr_svn151_64"

><td id="64"><a href="#64">64</a></td></tr
><tr id="gr_svn151_65"

><td id="65"><a href="#65">65</a></td></tr
><tr id="gr_svn151_66"

><td id="66"><a href="#66">66</a></td></tr
><tr id="gr_svn151_67"

><td id="67"><a href="#67">67</a></td></tr
><tr id="gr_svn151_68"

><td id="68"><a href="#68">68</a></td></tr
><tr id="gr_svn151_69"

><td id="69"><a href="#69">69</a></td></tr
><tr id="gr_svn151_70"

><td id="70"><a href="#70">70</a></td></tr
><tr id="gr_svn151_71"

><td id="71"><a href="#71">71</a></td></tr
><tr id="gr_svn151_72"

><td id="72"><a href="#72">72</a></td></tr
><tr id="gr_svn151_73"

><td id="73"><a href="#73">73</a></td></tr
><tr id="gr_svn151_74"

><td id="74"><a href="#74">74</a></td></tr
><tr id="gr_svn151_75"

><td id="75"><a href="#75">75</a></td></tr
><tr id="gr_svn151_76"

><td id="76"><a href="#76">76</a></td></tr
><tr id="gr_svn151_77"

><td id="77"><a href="#77">77</a></td></tr
><tr id="gr_svn151_78"

><td id="78"><a href="#78">78</a></td></tr
><tr id="gr_svn151_79"

><td id="79"><a href="#79">79</a></td></tr
><tr id="gr_svn151_80"

><td id="80"><a href="#80">80</a></td></tr
><tr id="gr_svn151_81"

><td id="81"><a href="#81">81</a></td></tr
><tr id="gr_svn151_82"

><td id="82"><a href="#82">82</a></td></tr
><tr id="gr_svn151_83"

><td id="83"><a href="#83">83</a></td></tr
><tr id="gr_svn151_84"

><td id="84"><a href="#84">84</a></td></tr
><tr id="gr_svn151_85"

><td id="85"><a href="#85">85</a></td></tr
><tr id="gr_svn151_86"

><td id="86"><a href="#86">86</a></td></tr
><tr id="gr_svn151_87"

><td id="87"><a href="#87">87</a></td></tr
><tr id="gr_svn151_88"

><td id="88"><a href="#88">88</a></td></tr
><tr id="gr_svn151_89"

><td id="89"><a href="#89">89</a></td></tr
><tr id="gr_svn151_90"

><td id="90"><a href="#90">90</a></td></tr
><tr id="gr_svn151_91"

><td id="91"><a href="#91">91</a></td></tr
><tr id="gr_svn151_92"

><td id="92"><a href="#92">92</a></td></tr
><tr id="gr_svn151_93"

><td id="93"><a href="#93">93</a></td></tr
><tr id="gr_svn151_94"

><td id="94"><a href="#94">94</a></td></tr
><tr id="gr_svn151_95"

><td id="95"><a href="#95">95</a></td></tr
><tr id="gr_svn151_96"

><td id="96"><a href="#96">96</a></td></tr
><tr id="gr_svn151_97"

><td id="97"><a href="#97">97</a></td></tr
><tr id="gr_svn151_98"

><td id="98"><a href="#98">98</a></td></tr
><tr id="gr_svn151_99"

><td id="99"><a href="#99">99</a></td></tr
><tr id="gr_svn151_100"

><td id="100"><a href="#100">100</a></td></tr
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre class="prettyprint lang-cpp"><table id="src_table_0"><tr
id=sl_svn151_1

><td class="source">#include &quot;Platform.h&quot;<br></td></tr
><tr
id=sl_svn151_2

><td class="source"><br></td></tr
><tr
id=sl_svn151_3

><td class="source">/*<br></td></tr
><tr
id=sl_svn151_4

><td class="source"> * This file is derived from crc32.c from the zlib-1.1.3 distribution<br></td></tr
><tr
id=sl_svn151_5

><td class="source"> * by Jean-loup Gailly and Mark Adler.<br></td></tr
><tr
id=sl_svn151_6

><td class="source"> */<br></td></tr
><tr
id=sl_svn151_7

><td class="source"><br></td></tr
><tr
id=sl_svn151_8

><td class="source">/* crc32.c -- compute the CRC-32 of a data stream<br></td></tr
><tr
id=sl_svn151_9

><td class="source"> * Copyright (C) 1995-1998 Mark Adler<br></td></tr
><tr
id=sl_svn151_10

><td class="source"> * For conditions of distribution and use, see copyright notice in zlib.h<br></td></tr
><tr
id=sl_svn151_11

><td class="source"> */<br></td></tr
><tr
id=sl_svn151_12

><td class="source"><br></td></tr
><tr
id=sl_svn151_13

><td class="source"><br></td></tr
><tr
id=sl_svn151_14

><td class="source">/* ========================================================================<br></td></tr
><tr
id=sl_svn151_15

><td class="source"> * Table of CRC-32&#39;s of all single-byte values (made by make_crc_table)<br></td></tr
><tr
id=sl_svn151_16

><td class="source"> */<br></td></tr
><tr
id=sl_svn151_17

><td class="source">static const uint32_t crc_table[256] = {<br></td></tr
><tr
id=sl_svn151_18

><td class="source">  0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,<br></td></tr
><tr
id=sl_svn151_19

><td class="source">  0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,<br></td></tr
><tr
id=sl_svn151_20

><td class="source">  0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,<br></td></tr
><tr
id=sl_svn151_21

><td class="source">  0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,<br></td></tr
><tr
id=sl_svn151_22

><td class="source">  0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,<br></td></tr
><tr
id=sl_svn151_23

><td class="source">  0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,<br></td></tr
><tr
id=sl_svn151_24

><td class="source">  0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,<br></td></tr
><tr
id=sl_svn151_25

><td class="source">  0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,<br></td></tr
><tr
id=sl_svn151_26

><td class="source">  0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,<br></td></tr
><tr
id=sl_svn151_27

><td class="source">  0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,<br></td></tr
><tr
id=sl_svn151_28

><td class="source">  0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,<br></td></tr
><tr
id=sl_svn151_29

><td class="source">  0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,<br></td></tr
><tr
id=sl_svn151_30

><td class="source">  0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,<br></td></tr
><tr
id=sl_svn151_31

><td class="source">  0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,<br></td></tr
><tr
id=sl_svn151_32

><td class="source">  0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,<br></td></tr
><tr
id=sl_svn151_33

><td class="source">  0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,<br></td></tr
><tr
id=sl_svn151_34

><td class="source">  0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,<br></td></tr
><tr
id=sl_svn151_35

><td class="source">  0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,<br></td></tr
><tr
id=sl_svn151_36

><td class="source">  0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,<br></td></tr
><tr
id=sl_svn151_37

><td class="source">  0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,<br></td></tr
><tr
id=sl_svn151_38

><td class="source">  0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,<br></td></tr
><tr
id=sl_svn151_39

><td class="source">  0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,<br></td></tr
><tr
id=sl_svn151_40

><td class="source">  0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,<br></td></tr
><tr
id=sl_svn151_41

><td class="source">  0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,<br></td></tr
><tr
id=sl_svn151_42

><td class="source">  0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,<br></td></tr
><tr
id=sl_svn151_43

><td class="source">  0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,<br></td></tr
><tr
id=sl_svn151_44

><td class="source">  0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,<br></td></tr
><tr
id=sl_svn151_45

><td class="source">  0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,<br></td></tr
><tr
id=sl_svn151_46

><td class="source">  0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,<br></td></tr
><tr
id=sl_svn151_47

><td class="source">  0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,<br></td></tr
><tr
id=sl_svn151_48

><td class="source">  0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,<br></td></tr
><tr
id=sl_svn151_49

><td class="source">  0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,<br></td></tr
><tr
id=sl_svn151_50

><td class="source">  0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,<br></td></tr
><tr
id=sl_svn151_51

><td class="source">  0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,<br></td></tr
><tr
id=sl_svn151_52

><td class="source">  0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,<br></td></tr
><tr
id=sl_svn151_53

><td class="source">  0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,<br></td></tr
><tr
id=sl_svn151_54

><td class="source">  0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,<br></td></tr
><tr
id=sl_svn151_55

><td class="source">  0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,<br></td></tr
><tr
id=sl_svn151_56

><td class="source">  0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,<br></td></tr
><tr
id=sl_svn151_57

><td class="source">  0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,<br></td></tr
><tr
id=sl_svn151_58

><td class="source">  0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,<br></td></tr
><tr
id=sl_svn151_59

><td class="source">  0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,<br></td></tr
><tr
id=sl_svn151_60

><td class="source">  0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,<br></td></tr
><tr
id=sl_svn151_61

><td class="source">  0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,<br></td></tr
><tr
id=sl_svn151_62

><td class="source">  0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,<br></td></tr
><tr
id=sl_svn151_63

><td class="source">  0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,<br></td></tr
><tr
id=sl_svn151_64

><td class="source">  0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,<br></td></tr
><tr
id=sl_svn151_65

><td class="source">  0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,<br></td></tr
><tr
id=sl_svn151_66

><td class="source">  0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,<br></td></tr
><tr
id=sl_svn151_67

><td class="source">  0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,<br></td></tr
><tr
id=sl_svn151_68

><td class="source">  0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,<br></td></tr
><tr
id=sl_svn151_69

><td class="source">  0x2d02ef8dL<br></td></tr
><tr
id=sl_svn151_70

><td class="source">};<br></td></tr
><tr
id=sl_svn151_71

><td class="source"><br></td></tr
><tr
id=sl_svn151_72

><td class="source">/* ========================================================================= */<br></td></tr
><tr
id=sl_svn151_73

><td class="source"><br></td></tr
><tr
id=sl_svn151_74

><td class="source">#define DO1(buf) crc = crc_table[((int)crc ^ (*buf++)) &amp; 0xff] ^ (crc &gt;&gt; 8);<br></td></tr
><tr
id=sl_svn151_75

><td class="source">#define DO2(buf)  DO1(buf); DO1(buf);<br></td></tr
><tr
id=sl_svn151_76

><td class="source">#define DO4(buf)  DO2(buf); DO2(buf);<br></td></tr
><tr
id=sl_svn151_77

><td class="source">#define DO8(buf)  DO4(buf); DO4(buf);<br></td></tr
><tr
id=sl_svn151_78

><td class="source"><br></td></tr
><tr
id=sl_svn151_79

><td class="source">/* ========================================================================= */<br></td></tr
><tr
id=sl_svn151_80

><td class="source"><br></td></tr
><tr
id=sl_svn151_81

><td class="source">void crc32 ( const void * key, int len, uint32_t seed, void * out )<br></td></tr
><tr
id=sl_svn151_82

><td class="source">{<br></td></tr
><tr
id=sl_svn151_83

><td class="source">  uint8_t * buf = (uint8_t*)key;<br></td></tr
><tr
id=sl_svn151_84

><td class="source">  uint32_t crc = seed ^ 0xffffffffL;<br></td></tr
><tr
id=sl_svn151_85

><td class="source"><br></td></tr
><tr
id=sl_svn151_86

><td class="source">  while (len &gt;= 8)<br></td></tr
><tr
id=sl_svn151_87

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_88

><td class="source">    DO8(buf);<br></td></tr
><tr
id=sl_svn151_89

><td class="source">    len -= 8;<br></td></tr
><tr
id=sl_svn151_90

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_91

><td class="source"><br></td></tr
><tr
id=sl_svn151_92

><td class="source">  while(len--)<br></td></tr
><tr
id=sl_svn151_93

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_94

><td class="source">    DO1(buf);<br></td></tr
><tr
id=sl_svn151_95

><td class="source">  } <br></td></tr
><tr
id=sl_svn151_96

><td class="source"><br></td></tr
><tr
id=sl_svn151_97

><td class="source">  crc ^= 0xffffffffL;<br></td></tr
><tr
id=sl_svn151_98

><td class="source"><br></td></tr
><tr
id=sl_svn151_99

><td class="source">  *(uint32_t*)out = crc;<br></td></tr
><tr
id=sl_svn151_100

><td class="source">}<br></td></tr
></table></pre>
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
</td>
</tr></table>

 
<script type="text/javascript">
 var lineNumUnderMouse = -1;
 
 function gutterOver(num) {
 gutterOut();
 var newTR = document.getElementById('gr_svn151_' + num);
 if (newTR) {
 newTR.className = 'undermouse';
 }
 lineNumUnderMouse = num;
 }
 function gutterOut() {
 if (lineNumUnderMouse != -1) {
 var oldTR = document.getElementById(
 'gr_svn151_' + lineNumUnderMouse);
 if (oldTR) {
 oldTR.className = '';
 }
 lineNumUnderMouse = -1;
 }
 }
 var numsGenState = {table_base_id: 'nums_table_'};
 var srcGenState = {table_base_id: 'src_table_'};
 var alignerRunning = false;
 var startOver = false;
 function setLineNumberHeights() {
 if (alignerRunning) {
 startOver = true;
 return;
 }
 numsGenState.chunk_id = 0;
 numsGenState.table = document.getElementById('nums_table_0');
 numsGenState.row_num = 0;
 if (!numsGenState.table) {
 return; // Silently exit if no file is present.
 }
 srcGenState.chunk_id = 0;
 srcGenState.table = document.getElementById('src_table_0');
 srcGenState.row_num = 0;
 alignerRunning = true;
 continueToSetLineNumberHeights();
 }
 function rowGenerator(genState) {
 if (genState.row_num < genState.table.rows.length) {
 var currentRow = genState.table.rows[genState.row_num];
 genState.row_num++;
 return currentRow;
 }
 var newTable = document.getElementById(
 genState.table_base_id + (genState.chunk_id + 1));
 if (newTable) {
 genState.chunk_id++;
 genState.row_num = 0;
 genState.table = newTable;
 return genState.table.rows[0];
 }
 return null;
 }
 var MAX_ROWS_PER_PASS = 1000;
 function continueToSetLineNumberHeights() {
 var rowsInThisPass = 0;
 var numRow = 1;
 var srcRow = 1;
 while (numRow && srcRow && rowsInThisPass < MAX_ROWS_PER_PASS) {
 numRow = rowGenerator(numsGenState);
 srcRow = rowGenerator(srcGenState);
 rowsInThisPass++;
 if (numRow && srcRow) {
 if (numRow.offsetHeight != srcRow.offsetHeight) {
 numRow.firstChild.style.height = srcRow.offsetHeight + 'px';
 }
 }
 }
 if (rowsInThisPass >= MAX_ROWS_PER_PASS) {
 setTimeout(continueToSetLineNumberHeights, 10);
 } else {
 alignerRunning = false;
 if (startOver) {
 startOver = false;
 setTimeout(setLineNumberHeights, 500);
 }
 }
 }
 function initLineNumberHeights() {
 // Do 2 complete passes, because there can be races
 // between this code and prettify.
 startOver = true;
 setTimeout(setLineNumberHeights, 250);
 window.onresize = setLineNumberHeights;
 }
 initLineNumberHeights();
</script>

 
 
 <div id="log">
 <div style="text-align:right">
 <a class="ifCollapse" href="#" onclick="_toggleMeta(this); return false">Show details</a>
 <a class="ifExpand" href="#" onclick="_toggleMeta(this); return false">Hide details</a>
 </div>
 <div class="ifExpand">
 
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="changelog">
 <p>Change log</p>
 <div>
 <a href="/p/smhasher/source/detail?spec=svn151&amp;r=144">r144</a>
 by tanjent
 on Feb 29, 2012
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=144&amp;format=side&amp;path=/trunk/crc.cpp&amp;old_path=/trunk/crc.cpp&amp;old=90">Diff</a>
 </div>
 <pre>Merge branch chandlerc_dev</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/smhasher/source/detail?r=144&spec=svn151';
 var publish_url = '/p/smhasher/source/detail?r=144&spec=svn151#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk');
 changed_urls.push('/p/smhasher/source/browse/trunk?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/AvalancheTest.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/AvalancheTest.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/AvalancheTest.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/AvalancheTest.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Bitslice.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/Bitslice.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Bitvec.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/Bitvec.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Bitvec.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/Bitvec.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/CMakeLists.txt');
 changed_urls.push('/p/smhasher/source/browse/trunk/CMakeLists.txt?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/City.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/City.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/City.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/City.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/CityTest.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/CityTest.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/DifferentialTest.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/DifferentialTest.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/DifferentialTest.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/DifferentialTest.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Hashes.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/Hashes.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Hashes.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/Hashes.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/KeysetTest.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/KeysetTest.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/KeysetTest.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/KeysetTest.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/MurmurHash1.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/MurmurHash1.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/MurmurHash1.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/MurmurHash1.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/MurmurHash2.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/MurmurHash2.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/MurmurHash2.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/MurmurHash2.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/MurmurHash3.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/MurmurHash3.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/MurmurHash3.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/MurmurHash3.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Platform.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/Platform.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Platform.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/Platform.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Random.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/Random.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Random.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/Random.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/SpeedTest.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/SpeedTest.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/SpeedTest.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/SpeedTest.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Spooky.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/Spooky.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Spooky.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/Spooky.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/SpookyTest.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/SpookyTest.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Stats.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/Stats.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Stats.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/Stats.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/SuperFastHash.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/SuperFastHash.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Types.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/Types.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/Types.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/Types.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/crc.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/crc.cpp?r\x3d144\x26spec\x3dsvn151');
 
 var selected_path = '/trunk/crc.cpp';
 
 
 changed_paths.push('/trunk/lookup3.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/lookup3.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/main.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/main.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/md5.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/md5.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/pstdint.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/pstdint.h?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/sha1.cpp');
 changed_urls.push('/p/smhasher/source/browse/trunk/sha1.cpp?r\x3d144\x26spec\x3dsvn151');
 
 
 changed_paths.push('/trunk/sha1.h');
 changed_urls.push('/p/smhasher/source/browse/trunk/sha1.h?r\x3d144\x26spec\x3dsvn151');
 
 
 function getCurrentPageIndex() {
 for (var i = 0; i < changed_paths.length; i++) {
 if (selected_path == changed_paths[i]) {
 return i;
 }
 }
 }
 function getNextPage() {
 var i = getCurrentPageIndex();
 if (i < changed_paths.length - 1) {
 return changed_urls[i + 1];
 }
 return null;
 }
 function getPreviousPage() {
 var i = getCurrentPageIndex();
 if (i > 0) {
 return changed_urls[i - 1];
 }
 return null;
 }
 function gotoNextPage() {
 var page = getNextPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoPreviousPage() {
 var page = getPreviousPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoDetailPage() {
 window.location = detail_url;
 }
 function gotoPublishPage() {
 window.location = publish_url;
 }
</script>

 
 <style type="text/css">
 #review_nav {
 border-top: 3px solid white;
 padding-top: 6px;
 margin-top: 1em;
 }
 #review_nav td {
 vertical-align: middle;
 }
 #review_nav select {
 margin: .5em 0;
 }
 </style>
 <div id="review_nav">
 <table><tr><td>Go to:&nbsp;</td><td>
 <select name="files_in_rev" onchange="window.location=this.value">
 
 <option value="/p/smhasher/source/browse/trunk?r=144&amp;spec=svn151"
 
 >/trunk</option>
 
 <option value="/p/smhasher/source/browse/trunk/AvalancheTest.cpp?r=144&amp;spec=svn151"
 
 >/trunk/AvalancheTest.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/AvalancheTest.h?r=144&amp;spec=svn151"
 
 >/trunk/AvalancheTest.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/Bitslice.cpp?r=144&amp;spec=svn151"
 
 >/trunk/Bitslice.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Bitvec.cpp?r=144&amp;spec=svn151"
 
 >/trunk/Bitvec.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Bitvec.h?r=144&amp;spec=svn151"
 
 >/trunk/Bitvec.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/CMakeLists.txt?r=144&amp;spec=svn151"
 
 >/trunk/CMakeLists.txt</option>
 
 <option value="/p/smhasher/source/browse/trunk/City.cpp?r=144&amp;spec=svn151"
 
 >/trunk/City.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/City.h?r=144&amp;spec=svn151"
 
 >/trunk/City.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/CityTest.cpp?r=144&amp;spec=svn151"
 
 >/trunk/CityTest.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/DifferentialTest.cpp?r=144&amp;spec=svn151"
 
 >/trunk/DifferentialTest.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/DifferentialTest.h?r=144&amp;spec=svn151"
 
 >/trunk/DifferentialTest.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/Hashes.cpp?r=144&amp;spec=svn151"
 
 >/trunk/Hashes.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Hashes.h?r=144&amp;spec=svn151"
 
 >/trunk/Hashes.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/KeysetTest.cpp?r=144&amp;spec=svn151"
 
 >/trunk/KeysetTest.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/KeysetTest.h?r=144&amp;spec=svn151"
 
 >/trunk/KeysetTest.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/MurmurHash1.cpp?r=144&amp;spec=svn151"
 
 >/trunk/MurmurHash1.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/MurmurHash1.h?r=144&amp;spec=svn151"
 
 >/trunk/MurmurHash1.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/MurmurHash2.cpp?r=144&amp;spec=svn151"
 
 >/trunk/MurmurHash2.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/MurmurHash2.h?r=144&amp;spec=svn151"
 
 >/trunk/MurmurHash2.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/MurmurHash3.cpp?r=144&amp;spec=svn151"
 
 >/trunk/MurmurHash3.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/MurmurHash3.h?r=144&amp;spec=svn151"
 
 >/trunk/MurmurHash3.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/Platform.cpp?r=144&amp;spec=svn151"
 
 >/trunk/Platform.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Platform.h?r=144&amp;spec=svn151"
 
 >/trunk/Platform.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/Random.cpp?r=144&amp;spec=svn151"
 
 >/trunk/Random.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Random.h?r=144&amp;spec=svn151"
 
 >/trunk/Random.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/SpeedTest.cpp?r=144&amp;spec=svn151"
 
 >/trunk/SpeedTest.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/SpeedTest.h?r=144&amp;spec=svn151"
 
 >/trunk/SpeedTest.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/Spooky.cpp?r=144&amp;spec=svn151"
 
 >/trunk/Spooky.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Spooky.h?r=144&amp;spec=svn151"
 
 >/trunk/Spooky.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/SpookyTest.cpp?r=144&amp;spec=svn151"
 
 >/trunk/SpookyTest.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Stats.cpp?r=144&amp;spec=svn151"
 
 >/trunk/Stats.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Stats.h?r=144&amp;spec=svn151"
 
 >/trunk/Stats.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/SuperFastHash.cpp?r=144&amp;spec=svn151"
 
 >/trunk/SuperFastHash.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Types.cpp?r=144&amp;spec=svn151"
 
 >/trunk/Types.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/Types.h?r=144&amp;spec=svn151"
 
 >/trunk/Types.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/crc.cpp?r=144&amp;spec=svn151"
 selected="selected"
 >/trunk/crc.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/lookup3.cpp?r=144&amp;spec=svn151"
 
 >/trunk/lookup3.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/main.cpp?r=144&amp;spec=svn151"
 
 >/trunk/main.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/md5.cpp?r=144&amp;spec=svn151"
 
 >/trunk/md5.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/pstdint.h?r=144&amp;spec=svn151"
 
 >/trunk/pstdint.h</option>
 
 <option value="/p/smhasher/source/browse/trunk/sha1.cpp?r=144&amp;spec=svn151"
 
 >/trunk/sha1.cpp</option>
 
 <option value="/p/smhasher/source/browse/trunk/sha1.h?r=144&amp;spec=svn151"
 
 >/trunk/sha1.h</option>
 
 </select>
 </td></tr></table>
 
 
 



 
 </div>
 
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="older_bubble">
 <p>Older revisions</p>
 
 
 <div class="closed" style="margin-bottom:3px;" >
 <a class="ifClosed" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/plus.gif" ></a>
 <a class="ifOpened" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/minus.gif" ></a>
 <a href="/p/smhasher/source/detail?spec=svn151&r=90">r90</a>
 by tanjent
 on Mar 19, 2011
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=90&amp;format=side&amp;path=/trunk/crc.cpp&amp;old_path=/trunk/crc.cpp&amp;old=87">Diff</a>
 <br>
 <pre class="ifOpened">Add startup self-test
Remove randhash (will fail self-test)
Remove QuickBrownFox (replaced by
VerificationTest)
De-tabulate all files</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <a class="ifClosed" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/plus.gif" ></a>
 <a class="ifOpened" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/minus.gif" ></a>
 <a href="/p/smhasher/source/detail?spec=svn151&r=87">r87</a>
 by tanjent
 on Mar 19, 2011
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=87&amp;format=side&amp;path=/trunk/crc.cpp&amp;old_path=/trunk/crc.cpp&amp;old=2">Diff</a>
 <br>
 <pre class="ifOpened">Cross-platform compliation fixes.
Everything should compile under GCC
now, but no guarantees that it runs
correctly yet...

...</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <a class="ifClosed" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/plus.gif" ></a>
 <a class="ifOpened" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/minus.gif" ></a>
 <a href="/p/smhasher/source/detail?spec=svn151&r=2">r2</a>
 by tanjent
 on Nov 1, 2010
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=2&amp;format=side&amp;path=/trunk/crc.cpp&amp;old_path=/trunk/crc.cpp&amp;old=">Diff</a>
 <br>
 <pre class="ifOpened">Initial source checkin</pre>
 </div>
 
 
 <a href="/p/smhasher/source/list?path=/trunk/crc.cpp&start=144">All revisions of this file</a>
 </div>
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="fileinfo_bubble">
 <p>File info</p>
 
 <div>Size: 4576 bytes,
 100 lines</div>
 
 <div><a href="//smhasher.googlecode.com/svn/trunk/crc.cpp">View raw file</a></div>
 </div>
 
 <div id="props">
 <p>File properties</p>
 <dl>
 
 <dt>svn:eol-style</dt>
 <dd>native</dd>
 
 </dl>
 </div>
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 </div>
 </div>


</div>

</div>
</div>

<script src="https://ssl.gstatic.com/codesite/ph/11104804043454007890/js/prettify/prettify.js"></script>
<script type="text/javascript">prettyPrint();</script>


<script src="https://ssl.gstatic.com/codesite/ph/11104804043454007890/js/source_file_scripts.js"></script>

 <script type="text/javascript" src="https://ssl.gstatic.com/codesite/ph/11104804043454007890/js/kibbles.js"></script>
 <script type="text/javascript">
 var lastStop = null;
 var initialized = false;
 
 function updateCursor(next, prev) {
 if (prev && prev.element) {
 prev.element.className = 'cursor_stop cursor_hidden';
 }
 if (next && next.element) {
 next.element.className = 'cursor_stop cursor';
 lastStop = next.index;
 }
 }
 
 function pubRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftDestroyed(data) {
 updateCursorForCell(data.cellId, 'nocursor');
 if (initialized) {
 reloadCursors();
 }
 }
 function reloadCursors() {
 kibbles.skipper.reset();
 loadCursors();
 if (lastStop != null) {
 kibbles.skipper.setCurrentStop(lastStop);
 }
 }
 // possibly the simplest way to insert any newly added comments
 // is to update the class of the corresponding cursor row,
 // then refresh the entire list of rows.
 function updateCursorForCell(cellId, className) {
 var cell = document.getElementById(cellId);
 // we have to go two rows back to find the cursor location
 var row = getPreviousElement(cell.parentNode);
 row.className = className;
 }
 // returns the previous element, ignores text nodes.
 function getPreviousElement(e) {
 var element = e.previousSibling;
 if (element.nodeType == 3) {
 element = element.previousSibling;
 }
 if (element && element.tagName) {
 return element;
 }
 }
 function loadCursors() {
 // register our elements with skipper
 var elements = CR_getElements('*', 'cursor_stop');
 var len = elements.length;
 for (var i = 0; i < len; i++) {
 var element = elements[i]; 
 element.className = 'cursor_stop cursor_hidden';
 kibbles.skipper.append(element);
 }
 }
 function toggleComments() {
 CR_toggleCommentDisplay();
 reloadCursors();
 }
 function keysOnLoadHandler() {
 // setup skipper
 kibbles.skipper.addStopListener(
 kibbles.skipper.LISTENER_TYPE.PRE, updateCursor);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_top', 50);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_bottom', 100);
 // Register our keys
 kibbles.skipper.addFwdKey("n");
 kibbles.skipper.addRevKey("p");
 kibbles.keys.addKeyPressListener(
 'u', function() { window.location = detail_url; });
 kibbles.keys.addKeyPressListener(
 'r', function() { window.location = detail_url + '#publish'; });
 
 kibbles.keys.addKeyPressListener('j', gotoNextPage);
 kibbles.keys.addKeyPressListener('k', gotoPreviousPage);
 
 
 }
 </script>
<script src="https://ssl.gstatic.com/codesite/ph/11104804043454007890/js/code_review_scripts.js"></script>
<script type="text/javascript">
 function showPublishInstructions() {
 var element = document.getElementById('review_instr');
 if (element) {
 element.className = 'opened';
 }
 }
 var codereviews;
 function revsOnLoadHandler() {
 // register our source container with the commenting code
 var paths = {'svn151': '/trunk/crc.cpp'}
 codereviews = CR_controller.setup(
 {"projectName": "smhasher", "loggedInUserEmail": "alanparsonsproject28@gmail.com", "token": "EDu_oR3WPXBU5nElWWso8i2GYY4:1390098706435", "projectHomeUrl": "/p/smhasher", "profileUrl": "/u/109814223914636253922/", "assetVersionPath": "https://ssl.gstatic.com/codesite/ph/11104804043454007890", "assetHostPath": "https://ssl.gstatic.com/codesite/ph", "domainName": null, "relativeBaseUrl": ""}, '', 'svn151', paths,
 CR_BrowseIntegrationFactory);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, showPublishInstructions);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_PUB_PLATE, pubRevealed);
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, draftRevealed);
 codereviews.registerActivityListener(CR_ActivityType.DISCARD_DRAFT_COMMENT, draftDestroyed);
 
 
 
 
 
 
 
 var initialized = true;
 reloadCursors();
 }
 window.onload = function() {keysOnLoadHandler(); revsOnLoadHandler();};

</script>
<script type="text/javascript" src="https://ssl.gstatic.com/codesite/ph/11104804043454007890/js/dit_scripts.js"></script>

 
 
 
 <script type="text/javascript" src="https://ssl.gstatic.com/codesite/ph/11104804043454007890/js/ph_core.js"></script>
 
 
 
 
</div> 

<div id="footer" dir="ltr">
 <div class="text">
 <a href="/projecthosting/terms.html">Terms</a> -
 <a href="http://www.google.com/privacy.html">Privacy</a> -
 <a href="/p/support/">Project Hosting Help</a>
 </div>
</div>
 <div class="hostedBy" style="margin-top: -20px;">
 <span style="vertical-align: top;">Powered by <a href="http://code.google.com/projecthosting/">Google Project Hosting</a></span>
 </div>

 
 


 
 </body>
</html>

