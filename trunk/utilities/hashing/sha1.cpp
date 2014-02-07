



<!DOCTYPE html>
<html>
<head>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link rel="icon" type="image/vnd.microsoft.icon" href="https://ssl.gstatic.com/codesite/ph/images/phosting.ico">
 
 
 <script type="text/javascript">
 
 
 
 
 var codesite_token = "pg-GjAOcQ1EyowsOl67mBUjDNVk:1390098686826";
 
 
 var CS_env = {"assetHostPath": "https://ssl.gstatic.com/codesite/ph", "projectName": "smhasher", "relativeBaseUrl": "", "domainName": null, "projectHomeUrl": "/p/smhasher", "loggedInUserEmail": "alanparsonsproject28@gmail.com", "profileUrl": "/u/109814223914636253922/", "token": "pg-GjAOcQ1EyowsOl67mBUjDNVk:1390098686826", "assetVersionPath": "https://ssl.gstatic.com/codesite/ph/11104804043454007890"};
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
 
 
 <title>sha1.cpp - 
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
 | <a href="https://www.google.com/accounts/Logout?continue=https%3A%2F%2Fcode.google.com%2Fp%2Fsmhasher%2Fsource%2Fbrowse%2Ftrunk%2Fsha1.cpp" 
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
 <span id="crumb_links" class="ifClosed"><a href="/p/smhasher/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span>sha1.cpp</span>
 
 


 </td>
 
 
 <td nowrap="nowrap" width="33%" align="center">
 <a href="/p/smhasher/source/browse/trunk/sha1.cpp?edit=1"
 ><img src="https://ssl.gstatic.com/codesite/ph/images/pencil-y14.png"
 class="edit_icon">Edit file</a>
 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper">
 <ul class="leftside">
 
 <li><a href="/p/smhasher/source/browse/trunk/sha1.cpp?r=128" title="Previous">&lsaquo;r128</a></li>
 
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
><tr id="gr_svn151_101"

><td id="101"><a href="#101">101</a></td></tr
><tr id="gr_svn151_102"

><td id="102"><a href="#102">102</a></td></tr
><tr id="gr_svn151_103"

><td id="103"><a href="#103">103</a></td></tr
><tr id="gr_svn151_104"

><td id="104"><a href="#104">104</a></td></tr
><tr id="gr_svn151_105"

><td id="105"><a href="#105">105</a></td></tr
><tr id="gr_svn151_106"

><td id="106"><a href="#106">106</a></td></tr
><tr id="gr_svn151_107"

><td id="107"><a href="#107">107</a></td></tr
><tr id="gr_svn151_108"

><td id="108"><a href="#108">108</a></td></tr
><tr id="gr_svn151_109"

><td id="109"><a href="#109">109</a></td></tr
><tr id="gr_svn151_110"

><td id="110"><a href="#110">110</a></td></tr
><tr id="gr_svn151_111"

><td id="111"><a href="#111">111</a></td></tr
><tr id="gr_svn151_112"

><td id="112"><a href="#112">112</a></td></tr
><tr id="gr_svn151_113"

><td id="113"><a href="#113">113</a></td></tr
><tr id="gr_svn151_114"

><td id="114"><a href="#114">114</a></td></tr
><tr id="gr_svn151_115"

><td id="115"><a href="#115">115</a></td></tr
><tr id="gr_svn151_116"

><td id="116"><a href="#116">116</a></td></tr
><tr id="gr_svn151_117"

><td id="117"><a href="#117">117</a></td></tr
><tr id="gr_svn151_118"

><td id="118"><a href="#118">118</a></td></tr
><tr id="gr_svn151_119"

><td id="119"><a href="#119">119</a></td></tr
><tr id="gr_svn151_120"

><td id="120"><a href="#120">120</a></td></tr
><tr id="gr_svn151_121"

><td id="121"><a href="#121">121</a></td></tr
><tr id="gr_svn151_122"

><td id="122"><a href="#122">122</a></td></tr
><tr id="gr_svn151_123"

><td id="123"><a href="#123">123</a></td></tr
><tr id="gr_svn151_124"

><td id="124"><a href="#124">124</a></td></tr
><tr id="gr_svn151_125"

><td id="125"><a href="#125">125</a></td></tr
><tr id="gr_svn151_126"

><td id="126"><a href="#126">126</a></td></tr
><tr id="gr_svn151_127"

><td id="127"><a href="#127">127</a></td></tr
><tr id="gr_svn151_128"

><td id="128"><a href="#128">128</a></td></tr
><tr id="gr_svn151_129"

><td id="129"><a href="#129">129</a></td></tr
><tr id="gr_svn151_130"

><td id="130"><a href="#130">130</a></td></tr
><tr id="gr_svn151_131"

><td id="131"><a href="#131">131</a></td></tr
><tr id="gr_svn151_132"

><td id="132"><a href="#132">132</a></td></tr
><tr id="gr_svn151_133"

><td id="133"><a href="#133">133</a></td></tr
><tr id="gr_svn151_134"

><td id="134"><a href="#134">134</a></td></tr
><tr id="gr_svn151_135"

><td id="135"><a href="#135">135</a></td></tr
><tr id="gr_svn151_136"

><td id="136"><a href="#136">136</a></td></tr
><tr id="gr_svn151_137"

><td id="137"><a href="#137">137</a></td></tr
><tr id="gr_svn151_138"

><td id="138"><a href="#138">138</a></td></tr
><tr id="gr_svn151_139"

><td id="139"><a href="#139">139</a></td></tr
><tr id="gr_svn151_140"

><td id="140"><a href="#140">140</a></td></tr
><tr id="gr_svn151_141"

><td id="141"><a href="#141">141</a></td></tr
><tr id="gr_svn151_142"

><td id="142"><a href="#142">142</a></td></tr
><tr id="gr_svn151_143"

><td id="143"><a href="#143">143</a></td></tr
><tr id="gr_svn151_144"

><td id="144"><a href="#144">144</a></td></tr
><tr id="gr_svn151_145"

><td id="145"><a href="#145">145</a></td></tr
><tr id="gr_svn151_146"

><td id="146"><a href="#146">146</a></td></tr
><tr id="gr_svn151_147"

><td id="147"><a href="#147">147</a></td></tr
><tr id="gr_svn151_148"

><td id="148"><a href="#148">148</a></td></tr
><tr id="gr_svn151_149"

><td id="149"><a href="#149">149</a></td></tr
><tr id="gr_svn151_150"

><td id="150"><a href="#150">150</a></td></tr
><tr id="gr_svn151_151"

><td id="151"><a href="#151">151</a></td></tr
><tr id="gr_svn151_152"

><td id="152"><a href="#152">152</a></td></tr
><tr id="gr_svn151_153"

><td id="153"><a href="#153">153</a></td></tr
><tr id="gr_svn151_154"

><td id="154"><a href="#154">154</a></td></tr
><tr id="gr_svn151_155"

><td id="155"><a href="#155">155</a></td></tr
><tr id="gr_svn151_156"

><td id="156"><a href="#156">156</a></td></tr
><tr id="gr_svn151_157"

><td id="157"><a href="#157">157</a></td></tr
><tr id="gr_svn151_158"

><td id="158"><a href="#158">158</a></td></tr
><tr id="gr_svn151_159"

><td id="159"><a href="#159">159</a></td></tr
><tr id="gr_svn151_160"

><td id="160"><a href="#160">160</a></td></tr
><tr id="gr_svn151_161"

><td id="161"><a href="#161">161</a></td></tr
><tr id="gr_svn151_162"

><td id="162"><a href="#162">162</a></td></tr
><tr id="gr_svn151_163"

><td id="163"><a href="#163">163</a></td></tr
><tr id="gr_svn151_164"

><td id="164"><a href="#164">164</a></td></tr
><tr id="gr_svn151_165"

><td id="165"><a href="#165">165</a></td></tr
><tr id="gr_svn151_166"

><td id="166"><a href="#166">166</a></td></tr
><tr id="gr_svn151_167"

><td id="167"><a href="#167">167</a></td></tr
><tr id="gr_svn151_168"

><td id="168"><a href="#168">168</a></td></tr
><tr id="gr_svn151_169"

><td id="169"><a href="#169">169</a></td></tr
><tr id="gr_svn151_170"

><td id="170"><a href="#170">170</a></td></tr
><tr id="gr_svn151_171"

><td id="171"><a href="#171">171</a></td></tr
><tr id="gr_svn151_172"

><td id="172"><a href="#172">172</a></td></tr
><tr id="gr_svn151_173"

><td id="173"><a href="#173">173</a></td></tr
><tr id="gr_svn151_174"

><td id="174"><a href="#174">174</a></td></tr
><tr id="gr_svn151_175"

><td id="175"><a href="#175">175</a></td></tr
><tr id="gr_svn151_176"

><td id="176"><a href="#176">176</a></td></tr
><tr id="gr_svn151_177"

><td id="177"><a href="#177">177</a></td></tr
><tr id="gr_svn151_178"

><td id="178"><a href="#178">178</a></td></tr
><tr id="gr_svn151_179"

><td id="179"><a href="#179">179</a></td></tr
><tr id="gr_svn151_180"

><td id="180"><a href="#180">180</a></td></tr
><tr id="gr_svn151_181"

><td id="181"><a href="#181">181</a></td></tr
><tr id="gr_svn151_182"

><td id="182"><a href="#182">182</a></td></tr
><tr id="gr_svn151_183"

><td id="183"><a href="#183">183</a></td></tr
><tr id="gr_svn151_184"

><td id="184"><a href="#184">184</a></td></tr
><tr id="gr_svn151_185"

><td id="185"><a href="#185">185</a></td></tr
><tr id="gr_svn151_186"

><td id="186"><a href="#186">186</a></td></tr
><tr id="gr_svn151_187"

><td id="187"><a href="#187">187</a></td></tr
><tr id="gr_svn151_188"

><td id="188"><a href="#188">188</a></td></tr
><tr id="gr_svn151_189"

><td id="189"><a href="#189">189</a></td></tr
><tr id="gr_svn151_190"

><td id="190"><a href="#190">190</a></td></tr
><tr id="gr_svn151_191"

><td id="191"><a href="#191">191</a></td></tr
><tr id="gr_svn151_192"

><td id="192"><a href="#192">192</a></td></tr
><tr id="gr_svn151_193"

><td id="193"><a href="#193">193</a></td></tr
><tr id="gr_svn151_194"

><td id="194"><a href="#194">194</a></td></tr
><tr id="gr_svn151_195"

><td id="195"><a href="#195">195</a></td></tr
><tr id="gr_svn151_196"

><td id="196"><a href="#196">196</a></td></tr
><tr id="gr_svn151_197"

><td id="197"><a href="#197">197</a></td></tr
><tr id="gr_svn151_198"

><td id="198"><a href="#198">198</a></td></tr
><tr id="gr_svn151_199"

><td id="199"><a href="#199">199</a></td></tr
><tr id="gr_svn151_200"

><td id="200"><a href="#200">200</a></td></tr
><tr id="gr_svn151_201"

><td id="201"><a href="#201">201</a></td></tr
><tr id="gr_svn151_202"

><td id="202"><a href="#202">202</a></td></tr
><tr id="gr_svn151_203"

><td id="203"><a href="#203">203</a></td></tr
><tr id="gr_svn151_204"

><td id="204"><a href="#204">204</a></td></tr
><tr id="gr_svn151_205"

><td id="205"><a href="#205">205</a></td></tr
><tr id="gr_svn151_206"

><td id="206"><a href="#206">206</a></td></tr
><tr id="gr_svn151_207"

><td id="207"><a href="#207">207</a></td></tr
><tr id="gr_svn151_208"

><td id="208"><a href="#208">208</a></td></tr
><tr id="gr_svn151_209"

><td id="209"><a href="#209">209</a></td></tr
><tr id="gr_svn151_210"

><td id="210"><a href="#210">210</a></td></tr
><tr id="gr_svn151_211"

><td id="211"><a href="#211">211</a></td></tr
><tr id="gr_svn151_212"

><td id="212"><a href="#212">212</a></td></tr
><tr id="gr_svn151_213"

><td id="213"><a href="#213">213</a></td></tr
><tr id="gr_svn151_214"

><td id="214"><a href="#214">214</a></td></tr
><tr id="gr_svn151_215"

><td id="215"><a href="#215">215</a></td></tr
><tr id="gr_svn151_216"

><td id="216"><a href="#216">216</a></td></tr
><tr id="gr_svn151_217"

><td id="217"><a href="#217">217</a></td></tr
><tr id="gr_svn151_218"

><td id="218"><a href="#218">218</a></td></tr
><tr id="gr_svn151_219"

><td id="219"><a href="#219">219</a></td></tr
><tr id="gr_svn151_220"

><td id="220"><a href="#220">220</a></td></tr
><tr id="gr_svn151_221"

><td id="221"><a href="#221">221</a></td></tr
><tr id="gr_svn151_222"

><td id="222"><a href="#222">222</a></td></tr
><tr id="gr_svn151_223"

><td id="223"><a href="#223">223</a></td></tr
><tr id="gr_svn151_224"

><td id="224"><a href="#224">224</a></td></tr
><tr id="gr_svn151_225"

><td id="225"><a href="#225">225</a></td></tr
><tr id="gr_svn151_226"

><td id="226"><a href="#226">226</a></td></tr
><tr id="gr_svn151_227"

><td id="227"><a href="#227">227</a></td></tr
><tr id="gr_svn151_228"

><td id="228"><a href="#228">228</a></td></tr
><tr id="gr_svn151_229"

><td id="229"><a href="#229">229</a></td></tr
><tr id="gr_svn151_230"

><td id="230"><a href="#230">230</a></td></tr
><tr id="gr_svn151_231"

><td id="231"><a href="#231">231</a></td></tr
><tr id="gr_svn151_232"

><td id="232"><a href="#232">232</a></td></tr
><tr id="gr_svn151_233"

><td id="233"><a href="#233">233</a></td></tr
><tr id="gr_svn151_234"

><td id="234"><a href="#234">234</a></td></tr
><tr id="gr_svn151_235"

><td id="235"><a href="#235">235</a></td></tr
><tr id="gr_svn151_236"

><td id="236"><a href="#236">236</a></td></tr
><tr id="gr_svn151_237"

><td id="237"><a href="#237">237</a></td></tr
><tr id="gr_svn151_238"

><td id="238"><a href="#238">238</a></td></tr
><tr id="gr_svn151_239"

><td id="239"><a href="#239">239</a></td></tr
><tr id="gr_svn151_240"

><td id="240"><a href="#240">240</a></td></tr
><tr id="gr_svn151_241"

><td id="241"><a href="#241">241</a></td></tr
><tr id="gr_svn151_242"

><td id="242"><a href="#242">242</a></td></tr
><tr id="gr_svn151_243"

><td id="243"><a href="#243">243</a></td></tr
><tr id="gr_svn151_244"

><td id="244"><a href="#244">244</a></td></tr
><tr id="gr_svn151_245"

><td id="245"><a href="#245">245</a></td></tr
><tr id="gr_svn151_246"

><td id="246"><a href="#246">246</a></td></tr
><tr id="gr_svn151_247"

><td id="247"><a href="#247">247</a></td></tr
><tr id="gr_svn151_248"

><td id="248"><a href="#248">248</a></td></tr
><tr id="gr_svn151_249"

><td id="249"><a href="#249">249</a></td></tr
><tr id="gr_svn151_250"

><td id="250"><a href="#250">250</a></td></tr
><tr id="gr_svn151_251"

><td id="251"><a href="#251">251</a></td></tr
><tr id="gr_svn151_252"

><td id="252"><a href="#252">252</a></td></tr
><tr id="gr_svn151_253"

><td id="253"><a href="#253">253</a></td></tr
><tr id="gr_svn151_254"

><td id="254"><a href="#254">254</a></td></tr
><tr id="gr_svn151_255"

><td id="255"><a href="#255">255</a></td></tr
><tr id="gr_svn151_256"

><td id="256"><a href="#256">256</a></td></tr
><tr id="gr_svn151_257"

><td id="257"><a href="#257">257</a></td></tr
><tr id="gr_svn151_258"

><td id="258"><a href="#258">258</a></td></tr
><tr id="gr_svn151_259"

><td id="259"><a href="#259">259</a></td></tr
><tr id="gr_svn151_260"

><td id="260"><a href="#260">260</a></td></tr
><tr id="gr_svn151_261"

><td id="261"><a href="#261">261</a></td></tr
><tr id="gr_svn151_262"

><td id="262"><a href="#262">262</a></td></tr
><tr id="gr_svn151_263"

><td id="263"><a href="#263">263</a></td></tr
><tr id="gr_svn151_264"

><td id="264"><a href="#264">264</a></td></tr
><tr id="gr_svn151_265"

><td id="265"><a href="#265">265</a></td></tr
><tr id="gr_svn151_266"

><td id="266"><a href="#266">266</a></td></tr
><tr id="gr_svn151_267"

><td id="267"><a href="#267">267</a></td></tr
><tr id="gr_svn151_268"

><td id="268"><a href="#268">268</a></td></tr
><tr id="gr_svn151_269"

><td id="269"><a href="#269">269</a></td></tr
><tr id="gr_svn151_270"

><td id="270"><a href="#270">270</a></td></tr
><tr id="gr_svn151_271"

><td id="271"><a href="#271">271</a></td></tr
><tr id="gr_svn151_272"

><td id="272"><a href="#272">272</a></td></tr
><tr id="gr_svn151_273"

><td id="273"><a href="#273">273</a></td></tr
><tr id="gr_svn151_274"

><td id="274"><a href="#274">274</a></td></tr
><tr id="gr_svn151_275"

><td id="275"><a href="#275">275</a></td></tr
><tr id="gr_svn151_276"

><td id="276"><a href="#276">276</a></td></tr
><tr id="gr_svn151_277"

><td id="277"><a href="#277">277</a></td></tr
><tr id="gr_svn151_278"

><td id="278"><a href="#278">278</a></td></tr
><tr id="gr_svn151_279"

><td id="279"><a href="#279">279</a></td></tr
><tr id="gr_svn151_280"

><td id="280"><a href="#280">280</a></td></tr
><tr id="gr_svn151_281"

><td id="281"><a href="#281">281</a></td></tr
><tr id="gr_svn151_282"

><td id="282"><a href="#282">282</a></td></tr
><tr id="gr_svn151_283"

><td id="283"><a href="#283">283</a></td></tr
><tr id="gr_svn151_284"

><td id="284"><a href="#284">284</a></td></tr
><tr id="gr_svn151_285"

><td id="285"><a href="#285">285</a></td></tr
><tr id="gr_svn151_286"

><td id="286"><a href="#286">286</a></td></tr
><tr id="gr_svn151_287"

><td id="287"><a href="#287">287</a></td></tr
><tr id="gr_svn151_288"

><td id="288"><a href="#288">288</a></td></tr
><tr id="gr_svn151_289"

><td id="289"><a href="#289">289</a></td></tr
><tr id="gr_svn151_290"

><td id="290"><a href="#290">290</a></td></tr
><tr id="gr_svn151_291"

><td id="291"><a href="#291">291</a></td></tr
><tr id="gr_svn151_292"

><td id="292"><a href="#292">292</a></td></tr
><tr id="gr_svn151_293"

><td id="293"><a href="#293">293</a></td></tr
><tr id="gr_svn151_294"

><td id="294"><a href="#294">294</a></td></tr
><tr id="gr_svn151_295"

><td id="295"><a href="#295">295</a></td></tr
><tr id="gr_svn151_296"

><td id="296"><a href="#296">296</a></td></tr
><tr id="gr_svn151_297"

><td id="297"><a href="#297">297</a></td></tr
><tr id="gr_svn151_298"

><td id="298"><a href="#298">298</a></td></tr
><tr id="gr_svn151_299"

><td id="299"><a href="#299">299</a></td></tr
><tr id="gr_svn151_300"

><td id="300"><a href="#300">300</a></td></tr
><tr id="gr_svn151_301"

><td id="301"><a href="#301">301</a></td></tr
><tr id="gr_svn151_302"

><td id="302"><a href="#302">302</a></td></tr
><tr id="gr_svn151_303"

><td id="303"><a href="#303">303</a></td></tr
><tr id="gr_svn151_304"

><td id="304"><a href="#304">304</a></td></tr
><tr id="gr_svn151_305"

><td id="305"><a href="#305">305</a></td></tr
><tr id="gr_svn151_306"

><td id="306"><a href="#306">306</a></td></tr
><tr id="gr_svn151_307"

><td id="307"><a href="#307">307</a></td></tr
><tr id="gr_svn151_308"

><td id="308"><a href="#308">308</a></td></tr
><tr id="gr_svn151_309"

><td id="309"><a href="#309">309</a></td></tr
><tr id="gr_svn151_310"

><td id="310"><a href="#310">310</a></td></tr
><tr id="gr_svn151_311"

><td id="311"><a href="#311">311</a></td></tr
><tr id="gr_svn151_312"

><td id="312"><a href="#312">312</a></td></tr
><tr id="gr_svn151_313"

><td id="313"><a href="#313">313</a></td></tr
><tr id="gr_svn151_314"

><td id="314"><a href="#314">314</a></td></tr
><tr id="gr_svn151_315"

><td id="315"><a href="#315">315</a></td></tr
><tr id="gr_svn151_316"

><td id="316"><a href="#316">316</a></td></tr
><tr id="gr_svn151_317"

><td id="317"><a href="#317">317</a></td></tr
><tr id="gr_svn151_318"

><td id="318"><a href="#318">318</a></td></tr
><tr id="gr_svn151_319"

><td id="319"><a href="#319">319</a></td></tr
><tr id="gr_svn151_320"

><td id="320"><a href="#320">320</a></td></tr
><tr id="gr_svn151_321"

><td id="321"><a href="#321">321</a></td></tr
><tr id="gr_svn151_322"

><td id="322"><a href="#322">322</a></td></tr
><tr id="gr_svn151_323"

><td id="323"><a href="#323">323</a></td></tr
><tr id="gr_svn151_324"

><td id="324"><a href="#324">324</a></td></tr
><tr id="gr_svn151_325"

><td id="325"><a href="#325">325</a></td></tr
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre class="prettyprint lang-cpp"><table id="src_table_0"><tr
id=sl_svn151_1

><td class="source">/*<br></td></tr
><tr
id=sl_svn151_2

><td class="source">SHA-1 in C<br></td></tr
><tr
id=sl_svn151_3

><td class="source">By Steve Reid &lt;sreid@sea-to-sky.net&gt;<br></td></tr
><tr
id=sl_svn151_4

><td class="source">100% Public Domain<br></td></tr
><tr
id=sl_svn151_5

><td class="source"><br></td></tr
><tr
id=sl_svn151_6

><td class="source">-----------------<br></td></tr
><tr
id=sl_svn151_7

><td class="source">Modified 7/98<br></td></tr
><tr
id=sl_svn151_8

><td class="source">By James H. Brown &lt;jbrown@burgoyne.com&gt;<br></td></tr
><tr
id=sl_svn151_9

><td class="source">Still 100% Public Domain<br></td></tr
><tr
id=sl_svn151_10

><td class="source"><br></td></tr
><tr
id=sl_svn151_11

><td class="source">Corrected a problem which generated improper hash values on 16 bit machines<br></td></tr
><tr
id=sl_svn151_12

><td class="source">Routine SHA1Update changed from<br></td></tr
><tr
id=sl_svn151_13

><td class="source">  void SHA1Update(SHA1_CTX* context, unsigned char* data, unsigned int<br></td></tr
><tr
id=sl_svn151_14

><td class="source">len)<br></td></tr
><tr
id=sl_svn151_15

><td class="source">to<br></td></tr
><tr
id=sl_svn151_16

><td class="source">  void SHA1Update(SHA1_CTX* context, unsigned char* data, unsigned<br></td></tr
><tr
id=sl_svn151_17

><td class="source">long len)<br></td></tr
><tr
id=sl_svn151_18

><td class="source"><br></td></tr
><tr
id=sl_svn151_19

><td class="source">The &#39;len&#39; parameter was declared an int which works fine on 32 bit machines.<br></td></tr
><tr
id=sl_svn151_20

><td class="source">However, on 16 bit machines an int is too small for the shifts being done<br></td></tr
><tr
id=sl_svn151_21

><td class="source">against<br></td></tr
><tr
id=sl_svn151_22

><td class="source">it.  This caused the hash function to generate incorrect values if len was<br></td></tr
><tr
id=sl_svn151_23

><td class="source">greater than 8191 (8K - 1) due to the &#39;len &lt;&lt; 3&#39; on line 3 of SHA1Update().<br></td></tr
><tr
id=sl_svn151_24

><td class="source"><br></td></tr
><tr
id=sl_svn151_25

><td class="source">Since the file IO in main() reads 16K at a time, any file 8K or larger would<br></td></tr
><tr
id=sl_svn151_26

><td class="source">be guaranteed to generate the wrong hash (e.g. Test Vector #3, a million<br></td></tr
><tr
id=sl_svn151_27

><td class="source">&quot;a&quot;s).<br></td></tr
><tr
id=sl_svn151_28

><td class="source"><br></td></tr
><tr
id=sl_svn151_29

><td class="source">I also changed the declaration of variables i &amp; j in SHA1Update to<br></td></tr
><tr
id=sl_svn151_30

><td class="source">unsigned long from unsigned int for the same reason.<br></td></tr
><tr
id=sl_svn151_31

><td class="source"><br></td></tr
><tr
id=sl_svn151_32

><td class="source">These changes should make no difference to any 32 bit implementations since<br></td></tr
><tr
id=sl_svn151_33

><td class="source">an<br></td></tr
><tr
id=sl_svn151_34

><td class="source">int and a long are the same size in those environments.<br></td></tr
><tr
id=sl_svn151_35

><td class="source"><br></td></tr
><tr
id=sl_svn151_36

><td class="source">--<br></td></tr
><tr
id=sl_svn151_37

><td class="source">I also corrected a few compiler warnings generated by Borland C.<br></td></tr
><tr
id=sl_svn151_38

><td class="source">1. Added #include &lt;process.h&gt; for exit() prototype<br></td></tr
><tr
id=sl_svn151_39

><td class="source">2. Removed unused variable &#39;j&#39; in SHA1Final<br></td></tr
><tr
id=sl_svn151_40

><td class="source">3. Changed exit(0) to return(0) at end of main.<br></td></tr
><tr
id=sl_svn151_41

><td class="source"><br></td></tr
><tr
id=sl_svn151_42

><td class="source">ALL changes I made can be located by searching for comments containing &#39;JHB&#39;<br></td></tr
><tr
id=sl_svn151_43

><td class="source">-----------------<br></td></tr
><tr
id=sl_svn151_44

><td class="source">Modified 8/98<br></td></tr
><tr
id=sl_svn151_45

><td class="source">By Steve Reid &lt;sreid@sea-to-sky.net&gt;<br></td></tr
><tr
id=sl_svn151_46

><td class="source">Still 100% public domain<br></td></tr
><tr
id=sl_svn151_47

><td class="source"><br></td></tr
><tr
id=sl_svn151_48

><td class="source">1- Removed #include &lt;process.h&gt; and used return() instead of exit()<br></td></tr
><tr
id=sl_svn151_49

><td class="source">2- Fixed overwriting of finalcount in SHA1Final() (discovered by Chris Hall)<br></td></tr
><tr
id=sl_svn151_50

><td class="source">3- Changed email address from steve@edmweb.com to sreid@sea-to-sky.net<br></td></tr
><tr
id=sl_svn151_51

><td class="source"><br></td></tr
><tr
id=sl_svn151_52

><td class="source">-----------------<br></td></tr
><tr
id=sl_svn151_53

><td class="source">Modified 4/01<br></td></tr
><tr
id=sl_svn151_54

><td class="source">By Saul Kravitz &lt;Saul.Kravitz@celera.com&gt;<br></td></tr
><tr
id=sl_svn151_55

><td class="source">Still 100% PD<br></td></tr
><tr
id=sl_svn151_56

><td class="source">Modified to run on Compaq Alpha hardware.<br></td></tr
><tr
id=sl_svn151_57

><td class="source"><br></td></tr
><tr
id=sl_svn151_58

><td class="source">-----------------<br></td></tr
><tr
id=sl_svn151_59

><td class="source">Modified 07/2002<br></td></tr
><tr
id=sl_svn151_60

><td class="source">By Ralph Giles &lt;giles@ghostscript.com&gt;<br></td></tr
><tr
id=sl_svn151_61

><td class="source">Still 100% public domain<br></td></tr
><tr
id=sl_svn151_62

><td class="source">modified for use with stdint types, autoconf<br></td></tr
><tr
id=sl_svn151_63

><td class="source">code cleanup, removed attribution comments<br></td></tr
><tr
id=sl_svn151_64

><td class="source">switched SHA1Final() argument order for consistency<br></td></tr
><tr
id=sl_svn151_65

><td class="source">use SHA1_ prefix for public api<br></td></tr
><tr
id=sl_svn151_66

><td class="source">move public api to sha1.h<br></td></tr
><tr
id=sl_svn151_67

><td class="source">*/<br></td></tr
><tr
id=sl_svn151_68

><td class="source"><br></td></tr
><tr
id=sl_svn151_69

><td class="source">/*<br></td></tr
><tr
id=sl_svn151_70

><td class="source">Test Vectors (from FIPS PUB 180-1)<br></td></tr
><tr
id=sl_svn151_71

><td class="source">&quot;abc&quot;<br></td></tr
><tr
id=sl_svn151_72

><td class="source">  A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D<br></td></tr
><tr
id=sl_svn151_73

><td class="source">&quot;abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq&quot;<br></td></tr
><tr
id=sl_svn151_74

><td class="source">  84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1<br></td></tr
><tr
id=sl_svn151_75

><td class="source">A million repetitions of &quot;a&quot;<br></td></tr
><tr
id=sl_svn151_76

><td class="source">  34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F<br></td></tr
><tr
id=sl_svn151_77

><td class="source">*/<br></td></tr
><tr
id=sl_svn151_78

><td class="source"><br></td></tr
><tr
id=sl_svn151_79

><td class="source">#include &lt;stdio.h&gt;<br></td></tr
><tr
id=sl_svn151_80

><td class="source">#include &lt;string.h&gt;<br></td></tr
><tr
id=sl_svn151_81

><td class="source">#include &lt;stdlib.h&gt;<br></td></tr
><tr
id=sl_svn151_82

><td class="source"><br></td></tr
><tr
id=sl_svn151_83

><td class="source">#include &quot;sha1.h&quot;<br></td></tr
><tr
id=sl_svn151_84

><td class="source"><br></td></tr
><tr
id=sl_svn151_85

><td class="source">#if defined(_MSC_VER)<br></td></tr
><tr
id=sl_svn151_86

><td class="source">#pragma warning(disable : 4267)<br></td></tr
><tr
id=sl_svn151_87

><td class="source">#pragma warning(disable : 4996)<br></td></tr
><tr
id=sl_svn151_88

><td class="source">#pragma warning(disable : 4100)<br></td></tr
><tr
id=sl_svn151_89

><td class="source">#endif<br></td></tr
><tr
id=sl_svn151_90

><td class="source"><br></td></tr
><tr
id=sl_svn151_91

><td class="source">void SHA1_Transform(uint32_t state[5], const uint8_t buffer[64]);<br></td></tr
><tr
id=sl_svn151_92

><td class="source"><br></td></tr
><tr
id=sl_svn151_93

><td class="source">#define rol ROTL32<br></td></tr
><tr
id=sl_svn151_94

><td class="source"><br></td></tr
><tr
id=sl_svn151_95

><td class="source">/* blk0() and blk() perform the initial expand. */<br></td></tr
><tr
id=sl_svn151_96

><td class="source">/* I got the idea of expanding during the round function from SSLeay */<br></td></tr
><tr
id=sl_svn151_97

><td class="source">/* FIXME: can we do this in an endian-proof way? */<br></td></tr
><tr
id=sl_svn151_98

><td class="source"><br></td></tr
><tr
id=sl_svn151_99

><td class="source">#ifdef WORDS_BIGENDIAN<br></td></tr
><tr
id=sl_svn151_100

><td class="source">#define blk0(i) block-&gt;l[i]<br></td></tr
><tr
id=sl_svn151_101

><td class="source">#else<br></td></tr
><tr
id=sl_svn151_102

><td class="source">#define blk0(i) (block-&gt;l[i] = (rol(block-&gt;l[i],24)&amp;0xFF00FF00) | (rol(block-&gt;l[i],8)&amp;0x00FF00FF))<br></td></tr
><tr
id=sl_svn151_103

><td class="source">#endif<br></td></tr
><tr
id=sl_svn151_104

><td class="source">#define blk(i) (block-&gt;l[i&amp;15] = rol(block-&gt;l[(i+13)&amp;15]^block-&gt;l[(i+8)&amp;15] ^ block-&gt;l[(i+2)&amp;15]^block-&gt;l[i&amp;15],1))<br></td></tr
><tr
id=sl_svn151_105

><td class="source"><br></td></tr
><tr
id=sl_svn151_106

><td class="source">/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */<br></td></tr
><tr
id=sl_svn151_107

><td class="source">#define R0(v,w,x,y,z,i) z+=((w&amp;(x^y))^y)+blk0(i)+0x5A827999+rol(v,5);w=rol(w,30);<br></td></tr
><tr
id=sl_svn151_108

><td class="source">#define R1(v,w,x,y,z,i) z+=((w&amp;(x^y))^y)+blk(i)+0x5A827999+rol(v,5);w=rol(w,30);<br></td></tr
><tr
id=sl_svn151_109

><td class="source">#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+rol(v,5);w=rol(w,30);<br></td></tr
><tr
id=sl_svn151_110

><td class="source">#define R3(v,w,x,y,z,i) z+=(((w|x)&amp;y)|(w&amp;x))+blk(i)+0x8F1BBCDC+rol(v,5);w=rol(w,30);<br></td></tr
><tr
id=sl_svn151_111

><td class="source">#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+rol(v,5);w=rol(w,30);<br></td></tr
><tr
id=sl_svn151_112

><td class="source"><br></td></tr
><tr
id=sl_svn151_113

><td class="source"><br></td></tr
><tr
id=sl_svn151_114

><td class="source">/* Hash a single 512-bit block. This is the core of the algorithm. */<br></td></tr
><tr
id=sl_svn151_115

><td class="source">void SHA1_Transform(uint32_t state[5], const uint8_t buffer[64])<br></td></tr
><tr
id=sl_svn151_116

><td class="source">{<br></td></tr
><tr
id=sl_svn151_117

><td class="source">    uint32_t a, b, c, d, e;<br></td></tr
><tr
id=sl_svn151_118

><td class="source">    typedef union {<br></td></tr
><tr
id=sl_svn151_119

><td class="source">        uint8_t c[64];<br></td></tr
><tr
id=sl_svn151_120

><td class="source">        uint32_t l[16];<br></td></tr
><tr
id=sl_svn151_121

><td class="source">    } CHAR64LONG16;<br></td></tr
><tr
id=sl_svn151_122

><td class="source">    CHAR64LONG16* block;<br></td></tr
><tr
id=sl_svn151_123

><td class="source"><br></td></tr
><tr
id=sl_svn151_124

><td class="source">    block = (CHAR64LONG16*)buffer;<br></td></tr
><tr
id=sl_svn151_125

><td class="source"><br></td></tr
><tr
id=sl_svn151_126

><td class="source">    /* Copy context-&gt;state[] to working vars */<br></td></tr
><tr
id=sl_svn151_127

><td class="source">    a = state[0];<br></td></tr
><tr
id=sl_svn151_128

><td class="source">    b = state[1];<br></td></tr
><tr
id=sl_svn151_129

><td class="source">    c = state[2];<br></td></tr
><tr
id=sl_svn151_130

><td class="source">    d = state[3];<br></td></tr
><tr
id=sl_svn151_131

><td class="source">    e = state[4];<br></td></tr
><tr
id=sl_svn151_132

><td class="source"><br></td></tr
><tr
id=sl_svn151_133

><td class="source">    /* 4 rounds of 20 operations each. Loop unrolled. */<br></td></tr
><tr
id=sl_svn151_134

><td class="source">    R0(a,b,c,d,e, 0); R0(e,a,b,c,d, 1); R0(d,e,a,b,c, 2); R0(c,d,e,a,b, 3);<br></td></tr
><tr
id=sl_svn151_135

><td class="source">    R0(b,c,d,e,a, 4); R0(a,b,c,d,e, 5); R0(e,a,b,c,d, 6); R0(d,e,a,b,c, 7);<br></td></tr
><tr
id=sl_svn151_136

><td class="source">    R0(c,d,e,a,b, 8); R0(b,c,d,e,a, 9); R0(a,b,c,d,e,10); R0(e,a,b,c,d,11);<br></td></tr
><tr
id=sl_svn151_137

><td class="source">    R0(d,e,a,b,c,12); R0(c,d,e,a,b,13); R0(b,c,d,e,a,14); R0(a,b,c,d,e,15);<br></td></tr
><tr
id=sl_svn151_138

><td class="source">    R1(e,a,b,c,d,16); R1(d,e,a,b,c,17); R1(c,d,e,a,b,18); R1(b,c,d,e,a,19);<br></td></tr
><tr
id=sl_svn151_139

><td class="source">    R2(a,b,c,d,e,20); R2(e,a,b,c,d,21); R2(d,e,a,b,c,22); R2(c,d,e,a,b,23);<br></td></tr
><tr
id=sl_svn151_140

><td class="source">    R2(b,c,d,e,a,24); R2(a,b,c,d,e,25); R2(e,a,b,c,d,26); R2(d,e,a,b,c,27);<br></td></tr
><tr
id=sl_svn151_141

><td class="source">    R2(c,d,e,a,b,28); R2(b,c,d,e,a,29); R2(a,b,c,d,e,30); R2(e,a,b,c,d,31);<br></td></tr
><tr
id=sl_svn151_142

><td class="source">    R2(d,e,a,b,c,32); R2(c,d,e,a,b,33); R2(b,c,d,e,a,34); R2(a,b,c,d,e,35);<br></td></tr
><tr
id=sl_svn151_143

><td class="source">    R2(e,a,b,c,d,36); R2(d,e,a,b,c,37); R2(c,d,e,a,b,38); R2(b,c,d,e,a,39);<br></td></tr
><tr
id=sl_svn151_144

><td class="source">    R3(a,b,c,d,e,40); R3(e,a,b,c,d,41); R3(d,e,a,b,c,42); R3(c,d,e,a,b,43);<br></td></tr
><tr
id=sl_svn151_145

><td class="source">    R3(b,c,d,e,a,44); R3(a,b,c,d,e,45); R3(e,a,b,c,d,46); R3(d,e,a,b,c,47);<br></td></tr
><tr
id=sl_svn151_146

><td class="source">    R3(c,d,e,a,b,48); R3(b,c,d,e,a,49); R3(a,b,c,d,e,50); R3(e,a,b,c,d,51);<br></td></tr
><tr
id=sl_svn151_147

><td class="source">    R3(d,e,a,b,c,52); R3(c,d,e,a,b,53); R3(b,c,d,e,a,54); R3(a,b,c,d,e,55);<br></td></tr
><tr
id=sl_svn151_148

><td class="source">    R3(e,a,b,c,d,56); R3(d,e,a,b,c,57); R3(c,d,e,a,b,58); R3(b,c,d,e,a,59);<br></td></tr
><tr
id=sl_svn151_149

><td class="source">    R4(a,b,c,d,e,60); R4(e,a,b,c,d,61); R4(d,e,a,b,c,62); R4(c,d,e,a,b,63);<br></td></tr
><tr
id=sl_svn151_150

><td class="source">    R4(b,c,d,e,a,64); R4(a,b,c,d,e,65); R4(e,a,b,c,d,66); R4(d,e,a,b,c,67);<br></td></tr
><tr
id=sl_svn151_151

><td class="source">    R4(c,d,e,a,b,68); R4(b,c,d,e,a,69); R4(a,b,c,d,e,70); R4(e,a,b,c,d,71);<br></td></tr
><tr
id=sl_svn151_152

><td class="source">    R4(d,e,a,b,c,72); R4(c,d,e,a,b,73); R4(b,c,d,e,a,74); R4(a,b,c,d,e,75);<br></td></tr
><tr
id=sl_svn151_153

><td class="source">    R4(e,a,b,c,d,76); R4(d,e,a,b,c,77); R4(c,d,e,a,b,78); R4(b,c,d,e,a,79);<br></td></tr
><tr
id=sl_svn151_154

><td class="source"><br></td></tr
><tr
id=sl_svn151_155

><td class="source">    /* Add the working vars back into context.state[] */<br></td></tr
><tr
id=sl_svn151_156

><td class="source">    state[0] += a;<br></td></tr
><tr
id=sl_svn151_157

><td class="source">    state[1] += b;<br></td></tr
><tr
id=sl_svn151_158

><td class="source">    state[2] += c;<br></td></tr
><tr
id=sl_svn151_159

><td class="source">    state[3] += d;<br></td></tr
><tr
id=sl_svn151_160

><td class="source">    state[4] += e;<br></td></tr
><tr
id=sl_svn151_161

><td class="source"><br></td></tr
><tr
id=sl_svn151_162

><td class="source">    /* Wipe variables */<br></td></tr
><tr
id=sl_svn151_163

><td class="source">    a = b = c = d = e = 0;<br></td></tr
><tr
id=sl_svn151_164

><td class="source">}<br></td></tr
><tr
id=sl_svn151_165

><td class="source"><br></td></tr
><tr
id=sl_svn151_166

><td class="source"><br></td></tr
><tr
id=sl_svn151_167

><td class="source">/* SHA1Init - Initialize new context */<br></td></tr
><tr
id=sl_svn151_168

><td class="source">void SHA1_Init(SHA1_CTX* context)<br></td></tr
><tr
id=sl_svn151_169

><td class="source">{<br></td></tr
><tr
id=sl_svn151_170

><td class="source">    /* SHA1 initialization constants */<br></td></tr
><tr
id=sl_svn151_171

><td class="source">    context-&gt;state[0] = 0x67452301;<br></td></tr
><tr
id=sl_svn151_172

><td class="source">    context-&gt;state[1] = 0xEFCDAB89;<br></td></tr
><tr
id=sl_svn151_173

><td class="source">    context-&gt;state[2] = 0x98BADCFE;<br></td></tr
><tr
id=sl_svn151_174

><td class="source">    context-&gt;state[3] = 0x10325476;<br></td></tr
><tr
id=sl_svn151_175

><td class="source">    context-&gt;state[4] = 0xC3D2E1F0;<br></td></tr
><tr
id=sl_svn151_176

><td class="source">    context-&gt;count[0] = 0;<br></td></tr
><tr
id=sl_svn151_177

><td class="source">  context-&gt;count[1] = 0;<br></td></tr
><tr
id=sl_svn151_178

><td class="source">}<br></td></tr
><tr
id=sl_svn151_179

><td class="source"><br></td></tr
><tr
id=sl_svn151_180

><td class="source"><br></td></tr
><tr
id=sl_svn151_181

><td class="source">/* Run your data through this. */<br></td></tr
><tr
id=sl_svn151_182

><td class="source">void SHA1_Update(SHA1_CTX* context, const uint8_t* data, const size_t len)<br></td></tr
><tr
id=sl_svn151_183

><td class="source">{<br></td></tr
><tr
id=sl_svn151_184

><td class="source">    size_t i, j;<br></td></tr
><tr
id=sl_svn151_185

><td class="source"><br></td></tr
><tr
id=sl_svn151_186

><td class="source">    j = (context-&gt;count[0] &gt;&gt; 3) &amp; 63;<br></td></tr
><tr
id=sl_svn151_187

><td class="source">    if ((context-&gt;count[0] += len &lt;&lt; 3) &lt; (len &lt;&lt; 3)) context-&gt;count[1]++;<br></td></tr
><tr
id=sl_svn151_188

><td class="source"><br></td></tr
><tr
id=sl_svn151_189

><td class="source">    context-&gt;count[1] += (len &gt;&gt; 29);<br></td></tr
><tr
id=sl_svn151_190

><td class="source"><br></td></tr
><tr
id=sl_svn151_191

><td class="source">    if ((j + len) &gt; 63) <br></td></tr
><tr
id=sl_svn151_192

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_193

><td class="source">        memcpy(&amp;context-&gt;buffer[j], data, (i = 64-j));<br></td></tr
><tr
id=sl_svn151_194

><td class="source">        SHA1_Transform(context-&gt;state, context-&gt;buffer);<br></td></tr
><tr
id=sl_svn151_195

><td class="source"><br></td></tr
><tr
id=sl_svn151_196

><td class="source">        for ( ; i + 63 &lt; len; i += 64) <br></td></tr
><tr
id=sl_svn151_197

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_198

><td class="source">            SHA1_Transform(context-&gt;state, data + i);<br></td></tr
><tr
id=sl_svn151_199

><td class="source">        }<br></td></tr
><tr
id=sl_svn151_200

><td class="source"><br></td></tr
><tr
id=sl_svn151_201

><td class="source">        j = 0;<br></td></tr
><tr
id=sl_svn151_202

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_203

><td class="source">    else i = 0;<br></td></tr
><tr
id=sl_svn151_204

><td class="source">    memcpy(&amp;context-&gt;buffer[j], &amp;data[i], len - i);<br></td></tr
><tr
id=sl_svn151_205

><td class="source">}<br></td></tr
><tr
id=sl_svn151_206

><td class="source"><br></td></tr
><tr
id=sl_svn151_207

><td class="source"><br></td></tr
><tr
id=sl_svn151_208

><td class="source">/* Add padding and return the message digest. */<br></td></tr
><tr
id=sl_svn151_209

><td class="source">void SHA1_Final(SHA1_CTX* context, uint8_t digest[SHA1_DIGEST_SIZE])<br></td></tr
><tr
id=sl_svn151_210

><td class="source">{<br></td></tr
><tr
id=sl_svn151_211

><td class="source">    uint32_t i;<br></td></tr
><tr
id=sl_svn151_212

><td class="source">    uint8_t  finalcount[8];<br></td></tr
><tr
id=sl_svn151_213

><td class="source"><br></td></tr
><tr
id=sl_svn151_214

><td class="source">    for (i = 0; i &lt; 8; i++) {<br></td></tr
><tr
id=sl_svn151_215

><td class="source">        finalcount[i] = (unsigned char)((context-&gt;count[(i &gt;= 4 ? 0 : 1)]<br></td></tr
><tr
id=sl_svn151_216

><td class="source">         &gt;&gt; ((3-(i &amp; 3)) * 8) ) &amp; 255);  /* Endian independent */<br></td></tr
><tr
id=sl_svn151_217

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_218

><td class="source">    SHA1_Update(context, (uint8_t *)&quot;\200&quot;, 1);<br></td></tr
><tr
id=sl_svn151_219

><td class="source">    while ((context-&gt;count[0] &amp; 504) != 448) {<br></td></tr
><tr
id=sl_svn151_220

><td class="source">        SHA1_Update(context, (uint8_t *)&quot;\0&quot;, 1);<br></td></tr
><tr
id=sl_svn151_221

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_222

><td class="source">    SHA1_Update(context, finalcount, 8);  /* Should cause a SHA1_Transform() */<br></td></tr
><tr
id=sl_svn151_223

><td class="source">    for (i = 0; i &lt; SHA1_DIGEST_SIZE; i++) {<br></td></tr
><tr
id=sl_svn151_224

><td class="source">        digest[i] = (uint8_t)<br></td></tr
><tr
id=sl_svn151_225

><td class="source">         ((context-&gt;state[i&gt;&gt;2] &gt;&gt; ((3-(i &amp; 3)) * 8) ) &amp; 255);<br></td></tr
><tr
id=sl_svn151_226

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_227

><td class="source"><br></td></tr
><tr
id=sl_svn151_228

><td class="source">    /* Wipe variables */<br></td></tr
><tr
id=sl_svn151_229

><td class="source">    i = 0;<br></td></tr
><tr
id=sl_svn151_230

><td class="source">    memset(context-&gt;buffer, 0, 64);<br></td></tr
><tr
id=sl_svn151_231

><td class="source">    memset(context-&gt;state, 0, 20);<br></td></tr
><tr
id=sl_svn151_232

><td class="source">    memset(context-&gt;count, 0, 8);<br></td></tr
><tr
id=sl_svn151_233

><td class="source">    memset(finalcount, 0, 8);	/* SWR */<br></td></tr
><tr
id=sl_svn151_234

><td class="source">}<br></td></tr
><tr
id=sl_svn151_235

><td class="source"><br></td></tr
><tr
id=sl_svn151_236

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_237

><td class="source"><br></td></tr
><tr
id=sl_svn151_238

><td class="source">void sha1_32a ( const void * key, int len, uint32_t seed, void * out )<br></td></tr
><tr
id=sl_svn151_239

><td class="source">{<br></td></tr
><tr
id=sl_svn151_240

><td class="source">  SHA1_CTX context;<br></td></tr
><tr
id=sl_svn151_241

><td class="source"><br></td></tr
><tr
id=sl_svn151_242

><td class="source">  uint8_t digest[20];<br></td></tr
><tr
id=sl_svn151_243

><td class="source"><br></td></tr
><tr
id=sl_svn151_244

><td class="source">  SHA1_Init(&amp;context);<br></td></tr
><tr
id=sl_svn151_245

><td class="source">  SHA1_Update(&amp;context, (uint8_t*)key, len);<br></td></tr
><tr
id=sl_svn151_246

><td class="source">  SHA1_Final(&amp;context, digest);<br></td></tr
><tr
id=sl_svn151_247

><td class="source"><br></td></tr
><tr
id=sl_svn151_248

><td class="source">  memcpy(out,&amp;digest[0],4);<br></td></tr
><tr
id=sl_svn151_249

><td class="source">}<br></td></tr
><tr
id=sl_svn151_250

><td class="source"><br></td></tr
><tr
id=sl_svn151_251

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_252

><td class="source">// self test<br></td></tr
><tr
id=sl_svn151_253

><td class="source"><br></td></tr
><tr
id=sl_svn151_254

><td class="source">//#define TEST<br></td></tr
><tr
id=sl_svn151_255

><td class="source"><br></td></tr
><tr
id=sl_svn151_256

><td class="source">#ifdef TEST<br></td></tr
><tr
id=sl_svn151_257

><td class="source"><br></td></tr
><tr
id=sl_svn151_258

><td class="source">static char *test_data[] = {<br></td></tr
><tr
id=sl_svn151_259

><td class="source">    &quot;abc&quot;,<br></td></tr
><tr
id=sl_svn151_260

><td class="source">    &quot;abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq&quot;,<br></td></tr
><tr
id=sl_svn151_261

><td class="source">    &quot;A million repetitions of &#39;a&#39;&quot;};<br></td></tr
><tr
id=sl_svn151_262

><td class="source">static char *test_results[] = {<br></td></tr
><tr
id=sl_svn151_263

><td class="source">    &quot;A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D&quot;,<br></td></tr
><tr
id=sl_svn151_264

><td class="source">    &quot;84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1&quot;,<br></td></tr
><tr
id=sl_svn151_265

><td class="source">    &quot;34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F&quot;};<br></td></tr
><tr
id=sl_svn151_266

><td class="source"><br></td></tr
><tr
id=sl_svn151_267

><td class="source"><br></td></tr
><tr
id=sl_svn151_268

><td class="source">void digest_to_hex(const uint8_t digest[SHA1_DIGEST_SIZE], char *output)<br></td></tr
><tr
id=sl_svn151_269

><td class="source">{<br></td></tr
><tr
id=sl_svn151_270

><td class="source">    int i,j;<br></td></tr
><tr
id=sl_svn151_271

><td class="source">    char *c = output;<br></td></tr
><tr
id=sl_svn151_272

><td class="source"><br></td></tr
><tr
id=sl_svn151_273

><td class="source">    for (i = 0; i &lt; SHA1_DIGEST_SIZE/4; i++) {<br></td></tr
><tr
id=sl_svn151_274

><td class="source">        for (j = 0; j &lt; 4; j++) {<br></td></tr
><tr
id=sl_svn151_275

><td class="source">            sprintf(c,&quot;%02X&quot;, digest[i*4+j]);<br></td></tr
><tr
id=sl_svn151_276

><td class="source">            c += 2;<br></td></tr
><tr
id=sl_svn151_277

><td class="source">        }<br></td></tr
><tr
id=sl_svn151_278

><td class="source">        sprintf(c, &quot; &quot;);<br></td></tr
><tr
id=sl_svn151_279

><td class="source">        c += 1;<br></td></tr
><tr
id=sl_svn151_280

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_281

><td class="source">    *(c - 1) = &#39;\0&#39;;<br></td></tr
><tr
id=sl_svn151_282

><td class="source">}<br></td></tr
><tr
id=sl_svn151_283

><td class="source"><br></td></tr
><tr
id=sl_svn151_284

><td class="source">int main(int argc, char** argv)<br></td></tr
><tr
id=sl_svn151_285

><td class="source">{<br></td></tr
><tr
id=sl_svn151_286

><td class="source">    int k;<br></td></tr
><tr
id=sl_svn151_287

><td class="source">    SHA1_CTX context;<br></td></tr
><tr
id=sl_svn151_288

><td class="source">    uint8_t digest[20];<br></td></tr
><tr
id=sl_svn151_289

><td class="source">    char output[80];<br></td></tr
><tr
id=sl_svn151_290

><td class="source"><br></td></tr
><tr
id=sl_svn151_291

><td class="source">    fprintf(stdout, &quot;verifying SHA-1 implementation... &quot;);<br></td></tr
><tr
id=sl_svn151_292

><td class="source"><br></td></tr
><tr
id=sl_svn151_293

><td class="source">    for (k = 0; k &lt; 2; k++){<br></td></tr
><tr
id=sl_svn151_294

><td class="source">        SHA1_Init(&amp;context);<br></td></tr
><tr
id=sl_svn151_295

><td class="source">        SHA1_Update(&amp;context, (uint8_t*)test_data[k], strlen(test_data[k]));<br></td></tr
><tr
id=sl_svn151_296

><td class="source">        SHA1_Final(&amp;context, digest);<br></td></tr
><tr
id=sl_svn151_297

><td class="source">  digest_to_hex(digest, output);<br></td></tr
><tr
id=sl_svn151_298

><td class="source"><br></td></tr
><tr
id=sl_svn151_299

><td class="source">        if (strcmp(output, test_results[k])) {<br></td></tr
><tr
id=sl_svn151_300

><td class="source">            fprintf(stdout, &quot;FAIL\n&quot;);<br></td></tr
><tr
id=sl_svn151_301

><td class="source">            fprintf(stderr,&quot;* hash of \&quot;%s\&quot; incorrect:\n&quot;, test_data[k]);<br></td></tr
><tr
id=sl_svn151_302

><td class="source">            fprintf(stderr,&quot;\t%s returned\n&quot;, output);<br></td></tr
><tr
id=sl_svn151_303

><td class="source">            fprintf(stderr,&quot;\t%s is correct\n&quot;, test_results[k]);<br></td></tr
><tr
id=sl_svn151_304

><td class="source">            return (1);<br></td></tr
><tr
id=sl_svn151_305

><td class="source">        }<br></td></tr
><tr
id=sl_svn151_306

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_307

><td class="source">    /* million &#39;a&#39; vector we feed separately */<br></td></tr
><tr
id=sl_svn151_308

><td class="source">    SHA1_Init(&amp;context);<br></td></tr
><tr
id=sl_svn151_309

><td class="source">    for (k = 0; k &lt; 1000000; k++)<br></td></tr
><tr
id=sl_svn151_310

><td class="source">        SHA1_Update(&amp;context, (uint8_t*)&quot;a&quot;, 1);<br></td></tr
><tr
id=sl_svn151_311

><td class="source">    SHA1_Final(&amp;context, digest);<br></td></tr
><tr
id=sl_svn151_312

><td class="source">    digest_to_hex(digest, output);<br></td></tr
><tr
id=sl_svn151_313

><td class="source">    if (strcmp(output, test_results[2])) {<br></td></tr
><tr
id=sl_svn151_314

><td class="source">        fprintf(stdout, &quot;FAIL\n&quot;);<br></td></tr
><tr
id=sl_svn151_315

><td class="source">        fprintf(stderr,&quot;* hash of \&quot;%s\&quot; incorrect:\n&quot;, test_data[2]);<br></td></tr
><tr
id=sl_svn151_316

><td class="source">        fprintf(stderr,&quot;\t%s returned\n&quot;, output);<br></td></tr
><tr
id=sl_svn151_317

><td class="source">        fprintf(stderr,&quot;\t%s is correct\n&quot;, test_results[2]);<br></td></tr
><tr
id=sl_svn151_318

><td class="source">        return (1);<br></td></tr
><tr
id=sl_svn151_319

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_320

><td class="source"><br></td></tr
><tr
id=sl_svn151_321

><td class="source">    /* success */<br></td></tr
><tr
id=sl_svn151_322

><td class="source">    fprintf(stdout, &quot;ok\n&quot;);<br></td></tr
><tr
id=sl_svn151_323

><td class="source">    return(0);<br></td></tr
><tr
id=sl_svn151_324

><td class="source">}<br></td></tr
><tr
id=sl_svn151_325

><td class="source">#endif /* TEST */<br></td></tr
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
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=144&amp;format=side&amp;path=/trunk/sha1.cpp&amp;old_path=/trunk/sha1.cpp&amp;old=128">Diff</a>
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
 
 var selected_path = '/trunk/sha1.cpp';
 
 
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
 selected="selected"
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
 <a href="/p/smhasher/source/detail?spec=svn151&r=128">r128</a>
 by aappl...@google.com
 on Apr 8, 2011
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=128&amp;format=side&amp;path=/trunk/sha1.cpp&amp;old_path=/trunk/sha1.cpp&amp;old=90">Diff</a>
 <br>
 <pre class="ifOpened">Build fixes for clang, etc

</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <a class="ifClosed" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/plus.gif" ></a>
 <a class="ifOpened" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/minus.gif" ></a>
 <a href="/p/smhasher/source/detail?spec=svn151&r=90">r90</a>
 by tanjent
 on Mar 19, 2011
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=90&amp;format=side&amp;path=/trunk/sha1.cpp&amp;old_path=/trunk/sha1.cpp&amp;old=87">Diff</a>
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
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=87&amp;format=side&amp;path=/trunk/sha1.cpp&amp;old_path=/trunk/sha1.cpp&amp;old=5">Diff</a>
 <br>
 <pre class="ifOpened">Cross-platform compliation fixes.
Everything should compile under GCC
now, but no guarantees that it runs
correctly yet...

...</pre>
 </div>
 
 
 <a href="/p/smhasher/source/list?path=/trunk/sha1.cpp&start=144">All revisions of this file</a>
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
 
 <div>Size: 10230 bytes,
 325 lines</div>
 
 <div><a href="//smhasher.googlecode.com/svn/trunk/sha1.cpp">View raw file</a></div>
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
 var paths = {'svn151': '/trunk/sha1.cpp'}
 codereviews = CR_controller.setup(
 {"assetHostPath": "https://ssl.gstatic.com/codesite/ph", "projectName": "smhasher", "relativeBaseUrl": "", "domainName": null, "projectHomeUrl": "/p/smhasher", "loggedInUserEmail": "alanparsonsproject28@gmail.com", "profileUrl": "/u/109814223914636253922/", "token": "pg-GjAOcQ1EyowsOl67mBUjDNVk:1390098686826", "assetVersionPath": "https://ssl.gstatic.com/codesite/ph/11104804043454007890"}, '', 'svn151', paths,
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

