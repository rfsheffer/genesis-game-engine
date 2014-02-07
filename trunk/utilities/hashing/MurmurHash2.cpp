



<!DOCTYPE html>
<html>
<head>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link rel="icon" type="image/vnd.microsoft.icon" href="https://ssl.gstatic.com/codesite/ph/images/phosting.ico">
 
 
 <script type="text/javascript">
 
 
 
 
 var codesite_token = "M7iXhx73gCSrPjeUFEQWUu3LzZI:1390098585148";
 
 
 var CS_env = {"relativeBaseUrl": "", "domainName": null, "assetHostPath": "https://ssl.gstatic.com/codesite/ph", "assetVersionPath": "https://ssl.gstatic.com/codesite/ph/11104804043454007890", "profileUrl": "/u/109814223914636253922/", "projectHomeUrl": "/p/smhasher", "token": "M7iXhx73gCSrPjeUFEQWUu3LzZI:1390098585148", "projectName": "smhasher", "loggedInUserEmail": "alanparsonsproject28@gmail.com"};
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
 
 
 <title>MurmurHash2.cpp - 
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
 | <a href="https://www.google.com/accounts/Logout?continue=https%3A%2F%2Fcode.google.com%2Fp%2Fsmhasher%2Fsource%2Fbrowse%2Ftrunk%2FMurmurHash2.cpp" 
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
 <span id="crumb_links" class="ifClosed"><a href="/p/smhasher/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span>MurmurHash2.cpp</span>
 
 


 </td>
 
 
 <td nowrap="nowrap" width="33%" align="center">
 <a href="/p/smhasher/source/browse/trunk/MurmurHash2.cpp?edit=1"
 ><img src="https://ssl.gstatic.com/codesite/ph/images/pencil-y14.png"
 class="edit_icon">Edit file</a>
 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper">
 <ul class="leftside">
 
 <li><a href="/p/smhasher/source/browse/trunk/MurmurHash2.cpp?r=130" title="Previous">&lsaquo;r130</a></li>
 
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
><tr id="gr_svn151_326"

><td id="326"><a href="#326">326</a></td></tr
><tr id="gr_svn151_327"

><td id="327"><a href="#327">327</a></td></tr
><tr id="gr_svn151_328"

><td id="328"><a href="#328">328</a></td></tr
><tr id="gr_svn151_329"

><td id="329"><a href="#329">329</a></td></tr
><tr id="gr_svn151_330"

><td id="330"><a href="#330">330</a></td></tr
><tr id="gr_svn151_331"

><td id="331"><a href="#331">331</a></td></tr
><tr id="gr_svn151_332"

><td id="332"><a href="#332">332</a></td></tr
><tr id="gr_svn151_333"

><td id="333"><a href="#333">333</a></td></tr
><tr id="gr_svn151_334"

><td id="334"><a href="#334">334</a></td></tr
><tr id="gr_svn151_335"

><td id="335"><a href="#335">335</a></td></tr
><tr id="gr_svn151_336"

><td id="336"><a href="#336">336</a></td></tr
><tr id="gr_svn151_337"

><td id="337"><a href="#337">337</a></td></tr
><tr id="gr_svn151_338"

><td id="338"><a href="#338">338</a></td></tr
><tr id="gr_svn151_339"

><td id="339"><a href="#339">339</a></td></tr
><tr id="gr_svn151_340"

><td id="340"><a href="#340">340</a></td></tr
><tr id="gr_svn151_341"

><td id="341"><a href="#341">341</a></td></tr
><tr id="gr_svn151_342"

><td id="342"><a href="#342">342</a></td></tr
><tr id="gr_svn151_343"

><td id="343"><a href="#343">343</a></td></tr
><tr id="gr_svn151_344"

><td id="344"><a href="#344">344</a></td></tr
><tr id="gr_svn151_345"

><td id="345"><a href="#345">345</a></td></tr
><tr id="gr_svn151_346"

><td id="346"><a href="#346">346</a></td></tr
><tr id="gr_svn151_347"

><td id="347"><a href="#347">347</a></td></tr
><tr id="gr_svn151_348"

><td id="348"><a href="#348">348</a></td></tr
><tr id="gr_svn151_349"

><td id="349"><a href="#349">349</a></td></tr
><tr id="gr_svn151_350"

><td id="350"><a href="#350">350</a></td></tr
><tr id="gr_svn151_351"

><td id="351"><a href="#351">351</a></td></tr
><tr id="gr_svn151_352"

><td id="352"><a href="#352">352</a></td></tr
><tr id="gr_svn151_353"

><td id="353"><a href="#353">353</a></td></tr
><tr id="gr_svn151_354"

><td id="354"><a href="#354">354</a></td></tr
><tr id="gr_svn151_355"

><td id="355"><a href="#355">355</a></td></tr
><tr id="gr_svn151_356"

><td id="356"><a href="#356">356</a></td></tr
><tr id="gr_svn151_357"

><td id="357"><a href="#357">357</a></td></tr
><tr id="gr_svn151_358"

><td id="358"><a href="#358">358</a></td></tr
><tr id="gr_svn151_359"

><td id="359"><a href="#359">359</a></td></tr
><tr id="gr_svn151_360"

><td id="360"><a href="#360">360</a></td></tr
><tr id="gr_svn151_361"

><td id="361"><a href="#361">361</a></td></tr
><tr id="gr_svn151_362"

><td id="362"><a href="#362">362</a></td></tr
><tr id="gr_svn151_363"

><td id="363"><a href="#363">363</a></td></tr
><tr id="gr_svn151_364"

><td id="364"><a href="#364">364</a></td></tr
><tr id="gr_svn151_365"

><td id="365"><a href="#365">365</a></td></tr
><tr id="gr_svn151_366"

><td id="366"><a href="#366">366</a></td></tr
><tr id="gr_svn151_367"

><td id="367"><a href="#367">367</a></td></tr
><tr id="gr_svn151_368"

><td id="368"><a href="#368">368</a></td></tr
><tr id="gr_svn151_369"

><td id="369"><a href="#369">369</a></td></tr
><tr id="gr_svn151_370"

><td id="370"><a href="#370">370</a></td></tr
><tr id="gr_svn151_371"

><td id="371"><a href="#371">371</a></td></tr
><tr id="gr_svn151_372"

><td id="372"><a href="#372">372</a></td></tr
><tr id="gr_svn151_373"

><td id="373"><a href="#373">373</a></td></tr
><tr id="gr_svn151_374"

><td id="374"><a href="#374">374</a></td></tr
><tr id="gr_svn151_375"

><td id="375"><a href="#375">375</a></td></tr
><tr id="gr_svn151_376"

><td id="376"><a href="#376">376</a></td></tr
><tr id="gr_svn151_377"

><td id="377"><a href="#377">377</a></td></tr
><tr id="gr_svn151_378"

><td id="378"><a href="#378">378</a></td></tr
><tr id="gr_svn151_379"

><td id="379"><a href="#379">379</a></td></tr
><tr id="gr_svn151_380"

><td id="380"><a href="#380">380</a></td></tr
><tr id="gr_svn151_381"

><td id="381"><a href="#381">381</a></td></tr
><tr id="gr_svn151_382"

><td id="382"><a href="#382">382</a></td></tr
><tr id="gr_svn151_383"

><td id="383"><a href="#383">383</a></td></tr
><tr id="gr_svn151_384"

><td id="384"><a href="#384">384</a></td></tr
><tr id="gr_svn151_385"

><td id="385"><a href="#385">385</a></td></tr
><tr id="gr_svn151_386"

><td id="386"><a href="#386">386</a></td></tr
><tr id="gr_svn151_387"

><td id="387"><a href="#387">387</a></td></tr
><tr id="gr_svn151_388"

><td id="388"><a href="#388">388</a></td></tr
><tr id="gr_svn151_389"

><td id="389"><a href="#389">389</a></td></tr
><tr id="gr_svn151_390"

><td id="390"><a href="#390">390</a></td></tr
><tr id="gr_svn151_391"

><td id="391"><a href="#391">391</a></td></tr
><tr id="gr_svn151_392"

><td id="392"><a href="#392">392</a></td></tr
><tr id="gr_svn151_393"

><td id="393"><a href="#393">393</a></td></tr
><tr id="gr_svn151_394"

><td id="394"><a href="#394">394</a></td></tr
><tr id="gr_svn151_395"

><td id="395"><a href="#395">395</a></td></tr
><tr id="gr_svn151_396"

><td id="396"><a href="#396">396</a></td></tr
><tr id="gr_svn151_397"

><td id="397"><a href="#397">397</a></td></tr
><tr id="gr_svn151_398"

><td id="398"><a href="#398">398</a></td></tr
><tr id="gr_svn151_399"

><td id="399"><a href="#399">399</a></td></tr
><tr id="gr_svn151_400"

><td id="400"><a href="#400">400</a></td></tr
><tr id="gr_svn151_401"

><td id="401"><a href="#401">401</a></td></tr
><tr id="gr_svn151_402"

><td id="402"><a href="#402">402</a></td></tr
><tr id="gr_svn151_403"

><td id="403"><a href="#403">403</a></td></tr
><tr id="gr_svn151_404"

><td id="404"><a href="#404">404</a></td></tr
><tr id="gr_svn151_405"

><td id="405"><a href="#405">405</a></td></tr
><tr id="gr_svn151_406"

><td id="406"><a href="#406">406</a></td></tr
><tr id="gr_svn151_407"

><td id="407"><a href="#407">407</a></td></tr
><tr id="gr_svn151_408"

><td id="408"><a href="#408">408</a></td></tr
><tr id="gr_svn151_409"

><td id="409"><a href="#409">409</a></td></tr
><tr id="gr_svn151_410"

><td id="410"><a href="#410">410</a></td></tr
><tr id="gr_svn151_411"

><td id="411"><a href="#411">411</a></td></tr
><tr id="gr_svn151_412"

><td id="412"><a href="#412">412</a></td></tr
><tr id="gr_svn151_413"

><td id="413"><a href="#413">413</a></td></tr
><tr id="gr_svn151_414"

><td id="414"><a href="#414">414</a></td></tr
><tr id="gr_svn151_415"

><td id="415"><a href="#415">415</a></td></tr
><tr id="gr_svn151_416"

><td id="416"><a href="#416">416</a></td></tr
><tr id="gr_svn151_417"

><td id="417"><a href="#417">417</a></td></tr
><tr id="gr_svn151_418"

><td id="418"><a href="#418">418</a></td></tr
><tr id="gr_svn151_419"

><td id="419"><a href="#419">419</a></td></tr
><tr id="gr_svn151_420"

><td id="420"><a href="#420">420</a></td></tr
><tr id="gr_svn151_421"

><td id="421"><a href="#421">421</a></td></tr
><tr id="gr_svn151_422"

><td id="422"><a href="#422">422</a></td></tr
><tr id="gr_svn151_423"

><td id="423"><a href="#423">423</a></td></tr
><tr id="gr_svn151_424"

><td id="424"><a href="#424">424</a></td></tr
><tr id="gr_svn151_425"

><td id="425"><a href="#425">425</a></td></tr
><tr id="gr_svn151_426"

><td id="426"><a href="#426">426</a></td></tr
><tr id="gr_svn151_427"

><td id="427"><a href="#427">427</a></td></tr
><tr id="gr_svn151_428"

><td id="428"><a href="#428">428</a></td></tr
><tr id="gr_svn151_429"

><td id="429"><a href="#429">429</a></td></tr
><tr id="gr_svn151_430"

><td id="430"><a href="#430">430</a></td></tr
><tr id="gr_svn151_431"

><td id="431"><a href="#431">431</a></td></tr
><tr id="gr_svn151_432"

><td id="432"><a href="#432">432</a></td></tr
><tr id="gr_svn151_433"

><td id="433"><a href="#433">433</a></td></tr
><tr id="gr_svn151_434"

><td id="434"><a href="#434">434</a></td></tr
><tr id="gr_svn151_435"

><td id="435"><a href="#435">435</a></td></tr
><tr id="gr_svn151_436"

><td id="436"><a href="#436">436</a></td></tr
><tr id="gr_svn151_437"

><td id="437"><a href="#437">437</a></td></tr
><tr id="gr_svn151_438"

><td id="438"><a href="#438">438</a></td></tr
><tr id="gr_svn151_439"

><td id="439"><a href="#439">439</a></td></tr
><tr id="gr_svn151_440"

><td id="440"><a href="#440">440</a></td></tr
><tr id="gr_svn151_441"

><td id="441"><a href="#441">441</a></td></tr
><tr id="gr_svn151_442"

><td id="442"><a href="#442">442</a></td></tr
><tr id="gr_svn151_443"

><td id="443"><a href="#443">443</a></td></tr
><tr id="gr_svn151_444"

><td id="444"><a href="#444">444</a></td></tr
><tr id="gr_svn151_445"

><td id="445"><a href="#445">445</a></td></tr
><tr id="gr_svn151_446"

><td id="446"><a href="#446">446</a></td></tr
><tr id="gr_svn151_447"

><td id="447"><a href="#447">447</a></td></tr
><tr id="gr_svn151_448"

><td id="448"><a href="#448">448</a></td></tr
><tr id="gr_svn151_449"

><td id="449"><a href="#449">449</a></td></tr
><tr id="gr_svn151_450"

><td id="450"><a href="#450">450</a></td></tr
><tr id="gr_svn151_451"

><td id="451"><a href="#451">451</a></td></tr
><tr id="gr_svn151_452"

><td id="452"><a href="#452">452</a></td></tr
><tr id="gr_svn151_453"

><td id="453"><a href="#453">453</a></td></tr
><tr id="gr_svn151_454"

><td id="454"><a href="#454">454</a></td></tr
><tr id="gr_svn151_455"

><td id="455"><a href="#455">455</a></td></tr
><tr id="gr_svn151_456"

><td id="456"><a href="#456">456</a></td></tr
><tr id="gr_svn151_457"

><td id="457"><a href="#457">457</a></td></tr
><tr id="gr_svn151_458"

><td id="458"><a href="#458">458</a></td></tr
><tr id="gr_svn151_459"

><td id="459"><a href="#459">459</a></td></tr
><tr id="gr_svn151_460"

><td id="460"><a href="#460">460</a></td></tr
><tr id="gr_svn151_461"

><td id="461"><a href="#461">461</a></td></tr
><tr id="gr_svn151_462"

><td id="462"><a href="#462">462</a></td></tr
><tr id="gr_svn151_463"

><td id="463"><a href="#463">463</a></td></tr
><tr id="gr_svn151_464"

><td id="464"><a href="#464">464</a></td></tr
><tr id="gr_svn151_465"

><td id="465"><a href="#465">465</a></td></tr
><tr id="gr_svn151_466"

><td id="466"><a href="#466">466</a></td></tr
><tr id="gr_svn151_467"

><td id="467"><a href="#467">467</a></td></tr
><tr id="gr_svn151_468"

><td id="468"><a href="#468">468</a></td></tr
><tr id="gr_svn151_469"

><td id="469"><a href="#469">469</a></td></tr
><tr id="gr_svn151_470"

><td id="470"><a href="#470">470</a></td></tr
><tr id="gr_svn151_471"

><td id="471"><a href="#471">471</a></td></tr
><tr id="gr_svn151_472"

><td id="472"><a href="#472">472</a></td></tr
><tr id="gr_svn151_473"

><td id="473"><a href="#473">473</a></td></tr
><tr id="gr_svn151_474"

><td id="474"><a href="#474">474</a></td></tr
><tr id="gr_svn151_475"

><td id="475"><a href="#475">475</a></td></tr
><tr id="gr_svn151_476"

><td id="476"><a href="#476">476</a></td></tr
><tr id="gr_svn151_477"

><td id="477"><a href="#477">477</a></td></tr
><tr id="gr_svn151_478"

><td id="478"><a href="#478">478</a></td></tr
><tr id="gr_svn151_479"

><td id="479"><a href="#479">479</a></td></tr
><tr id="gr_svn151_480"

><td id="480"><a href="#480">480</a></td></tr
><tr id="gr_svn151_481"

><td id="481"><a href="#481">481</a></td></tr
><tr id="gr_svn151_482"

><td id="482"><a href="#482">482</a></td></tr
><tr id="gr_svn151_483"

><td id="483"><a href="#483">483</a></td></tr
><tr id="gr_svn151_484"

><td id="484"><a href="#484">484</a></td></tr
><tr id="gr_svn151_485"

><td id="485"><a href="#485">485</a></td></tr
><tr id="gr_svn151_486"

><td id="486"><a href="#486">486</a></td></tr
><tr id="gr_svn151_487"

><td id="487"><a href="#487">487</a></td></tr
><tr id="gr_svn151_488"

><td id="488"><a href="#488">488</a></td></tr
><tr id="gr_svn151_489"

><td id="489"><a href="#489">489</a></td></tr
><tr id="gr_svn151_490"

><td id="490"><a href="#490">490</a></td></tr
><tr id="gr_svn151_491"

><td id="491"><a href="#491">491</a></td></tr
><tr id="gr_svn151_492"

><td id="492"><a href="#492">492</a></td></tr
><tr id="gr_svn151_493"

><td id="493"><a href="#493">493</a></td></tr
><tr id="gr_svn151_494"

><td id="494"><a href="#494">494</a></td></tr
><tr id="gr_svn151_495"

><td id="495"><a href="#495">495</a></td></tr
><tr id="gr_svn151_496"

><td id="496"><a href="#496">496</a></td></tr
><tr id="gr_svn151_497"

><td id="497"><a href="#497">497</a></td></tr
><tr id="gr_svn151_498"

><td id="498"><a href="#498">498</a></td></tr
><tr id="gr_svn151_499"

><td id="499"><a href="#499">499</a></td></tr
><tr id="gr_svn151_500"

><td id="500"><a href="#500">500</a></td></tr
><tr id="gr_svn151_501"

><td id="501"><a href="#501">501</a></td></tr
><tr id="gr_svn151_502"

><td id="502"><a href="#502">502</a></td></tr
><tr id="gr_svn151_503"

><td id="503"><a href="#503">503</a></td></tr
><tr id="gr_svn151_504"

><td id="504"><a href="#504">504</a></td></tr
><tr id="gr_svn151_505"

><td id="505"><a href="#505">505</a></td></tr
><tr id="gr_svn151_506"

><td id="506"><a href="#506">506</a></td></tr
><tr id="gr_svn151_507"

><td id="507"><a href="#507">507</a></td></tr
><tr id="gr_svn151_508"

><td id="508"><a href="#508">508</a></td></tr
><tr id="gr_svn151_509"

><td id="509"><a href="#509">509</a></td></tr
><tr id="gr_svn151_510"

><td id="510"><a href="#510">510</a></td></tr
><tr id="gr_svn151_511"

><td id="511"><a href="#511">511</a></td></tr
><tr id="gr_svn151_512"

><td id="512"><a href="#512">512</a></td></tr
><tr id="gr_svn151_513"

><td id="513"><a href="#513">513</a></td></tr
><tr id="gr_svn151_514"

><td id="514"><a href="#514">514</a></td></tr
><tr id="gr_svn151_515"

><td id="515"><a href="#515">515</a></td></tr
><tr id="gr_svn151_516"

><td id="516"><a href="#516">516</a></td></tr
><tr id="gr_svn151_517"

><td id="517"><a href="#517">517</a></td></tr
><tr id="gr_svn151_518"

><td id="518"><a href="#518">518</a></td></tr
><tr id="gr_svn151_519"

><td id="519"><a href="#519">519</a></td></tr
><tr id="gr_svn151_520"

><td id="520"><a href="#520">520</a></td></tr
><tr id="gr_svn151_521"

><td id="521"><a href="#521">521</a></td></tr
><tr id="gr_svn151_522"

><td id="522"><a href="#522">522</a></td></tr
><tr id="gr_svn151_523"

><td id="523"><a href="#523">523</a></td></tr
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre class="prettyprint lang-cpp"><table id="src_table_0"><tr
id=sl_svn151_1

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_2

><td class="source">// MurmurHash2 was written by Austin Appleby, and is placed in the public<br></td></tr
><tr
id=sl_svn151_3

><td class="source">// domain. The author hereby disclaims copyright to this source code.<br></td></tr
><tr
id=sl_svn151_4

><td class="source"><br></td></tr
><tr
id=sl_svn151_5

><td class="source">// Note - This code makes a few assumptions about how your machine behaves -<br></td></tr
><tr
id=sl_svn151_6

><td class="source"><br></td></tr
><tr
id=sl_svn151_7

><td class="source">// 1. We can read a 4-byte value from any address without crashing<br></td></tr
><tr
id=sl_svn151_8

><td class="source">// 2. sizeof(int) == 4<br></td></tr
><tr
id=sl_svn151_9

><td class="source"><br></td></tr
><tr
id=sl_svn151_10

><td class="source">// And it has a few limitations -<br></td></tr
><tr
id=sl_svn151_11

><td class="source"><br></td></tr
><tr
id=sl_svn151_12

><td class="source">// 1. It will not work incrementally.<br></td></tr
><tr
id=sl_svn151_13

><td class="source">// 2. It will not produce the same results on little-endian and big-endian<br></td></tr
><tr
id=sl_svn151_14

><td class="source">//    machines.<br></td></tr
><tr
id=sl_svn151_15

><td class="source"><br></td></tr
><tr
id=sl_svn151_16

><td class="source">#include &quot;MurmurHash2.h&quot;<br></td></tr
><tr
id=sl_svn151_17

><td class="source"><br></td></tr
><tr
id=sl_svn151_18

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_19

><td class="source">// Platform-specific functions and macros<br></td></tr
><tr
id=sl_svn151_20

><td class="source"><br></td></tr
><tr
id=sl_svn151_21

><td class="source">// Microsoft Visual Studio<br></td></tr
><tr
id=sl_svn151_22

><td class="source"><br></td></tr
><tr
id=sl_svn151_23

><td class="source">#if defined(_MSC_VER)<br></td></tr
><tr
id=sl_svn151_24

><td class="source"><br></td></tr
><tr
id=sl_svn151_25

><td class="source">#define BIG_CONSTANT(x) (x)<br></td></tr
><tr
id=sl_svn151_26

><td class="source"><br></td></tr
><tr
id=sl_svn151_27

><td class="source">// Other compilers<br></td></tr
><tr
id=sl_svn151_28

><td class="source"><br></td></tr
><tr
id=sl_svn151_29

><td class="source">#else	// defined(_MSC_VER)<br></td></tr
><tr
id=sl_svn151_30

><td class="source"><br></td></tr
><tr
id=sl_svn151_31

><td class="source">#define BIG_CONSTANT(x) (x##LLU)<br></td></tr
><tr
id=sl_svn151_32

><td class="source"><br></td></tr
><tr
id=sl_svn151_33

><td class="source">#endif // !defined(_MSC_VER)<br></td></tr
><tr
id=sl_svn151_34

><td class="source"><br></td></tr
><tr
id=sl_svn151_35

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_36

><td class="source"><br></td></tr
><tr
id=sl_svn151_37

><td class="source">uint32_t MurmurHash2 ( const void * key, int len, uint32_t seed )<br></td></tr
><tr
id=sl_svn151_38

><td class="source">{<br></td></tr
><tr
id=sl_svn151_39

><td class="source">  // &#39;m&#39; and &#39;r&#39; are mixing constants generated offline.<br></td></tr
><tr
id=sl_svn151_40

><td class="source">  // They&#39;re not really &#39;magic&#39;, they just happen to work well.<br></td></tr
><tr
id=sl_svn151_41

><td class="source"><br></td></tr
><tr
id=sl_svn151_42

><td class="source">  const uint32_t m = 0x5bd1e995;<br></td></tr
><tr
id=sl_svn151_43

><td class="source">  const int r = 24;<br></td></tr
><tr
id=sl_svn151_44

><td class="source"><br></td></tr
><tr
id=sl_svn151_45

><td class="source">  // Initialize the hash to a &#39;random&#39; value<br></td></tr
><tr
id=sl_svn151_46

><td class="source"><br></td></tr
><tr
id=sl_svn151_47

><td class="source">  uint32_t h = seed ^ len;<br></td></tr
><tr
id=sl_svn151_48

><td class="source"><br></td></tr
><tr
id=sl_svn151_49

><td class="source">  // Mix 4 bytes at a time into the hash<br></td></tr
><tr
id=sl_svn151_50

><td class="source"><br></td></tr
><tr
id=sl_svn151_51

><td class="source">  const unsigned char * data = (const unsigned char *)key;<br></td></tr
><tr
id=sl_svn151_52

><td class="source"><br></td></tr
><tr
id=sl_svn151_53

><td class="source">  while(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_54

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_55

><td class="source">    uint32_t k = *(uint32_t*)data;<br></td></tr
><tr
id=sl_svn151_56

><td class="source"><br></td></tr
><tr
id=sl_svn151_57

><td class="source">    k *= m;<br></td></tr
><tr
id=sl_svn151_58

><td class="source">    k ^= k &gt;&gt; r;<br></td></tr
><tr
id=sl_svn151_59

><td class="source">    k *= m;<br></td></tr
><tr
id=sl_svn151_60

><td class="source"><br></td></tr
><tr
id=sl_svn151_61

><td class="source">    h *= m;<br></td></tr
><tr
id=sl_svn151_62

><td class="source">    h ^= k;<br></td></tr
><tr
id=sl_svn151_63

><td class="source"><br></td></tr
><tr
id=sl_svn151_64

><td class="source">    data += 4;<br></td></tr
><tr
id=sl_svn151_65

><td class="source">    len -= 4;<br></td></tr
><tr
id=sl_svn151_66

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_67

><td class="source"><br></td></tr
><tr
id=sl_svn151_68

><td class="source">  // Handle the last few bytes of the input array<br></td></tr
><tr
id=sl_svn151_69

><td class="source"><br></td></tr
><tr
id=sl_svn151_70

><td class="source">  switch(len)<br></td></tr
><tr
id=sl_svn151_71

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_72

><td class="source">  case 3: h ^= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_73

><td class="source">  case 2: h ^= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_74

><td class="source">  case 1: h ^= data[0];<br></td></tr
><tr
id=sl_svn151_75

><td class="source">      h *= m;<br></td></tr
><tr
id=sl_svn151_76

><td class="source">  };<br></td></tr
><tr
id=sl_svn151_77

><td class="source"><br></td></tr
><tr
id=sl_svn151_78

><td class="source">  // Do a few final mixes of the hash to ensure the last few<br></td></tr
><tr
id=sl_svn151_79

><td class="source">  // bytes are well-incorporated.<br></td></tr
><tr
id=sl_svn151_80

><td class="source"><br></td></tr
><tr
id=sl_svn151_81

><td class="source">  h ^= h &gt;&gt; 13;<br></td></tr
><tr
id=sl_svn151_82

><td class="source">  h *= m;<br></td></tr
><tr
id=sl_svn151_83

><td class="source">  h ^= h &gt;&gt; 15;<br></td></tr
><tr
id=sl_svn151_84

><td class="source"><br></td></tr
><tr
id=sl_svn151_85

><td class="source">  return h;<br></td></tr
><tr
id=sl_svn151_86

><td class="source">} <br></td></tr
><tr
id=sl_svn151_87

><td class="source"><br></td></tr
><tr
id=sl_svn151_88

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_89

><td class="source">// MurmurHash2, 64-bit versions, by Austin Appleby<br></td></tr
><tr
id=sl_svn151_90

><td class="source"><br></td></tr
><tr
id=sl_svn151_91

><td class="source">// The same caveats as 32-bit MurmurHash2 apply here - beware of alignment <br></td></tr
><tr
id=sl_svn151_92

><td class="source">// and endian-ness issues if used across multiple platforms.<br></td></tr
><tr
id=sl_svn151_93

><td class="source"><br></td></tr
><tr
id=sl_svn151_94

><td class="source">// 64-bit hash for 64-bit platforms<br></td></tr
><tr
id=sl_svn151_95

><td class="source"><br></td></tr
><tr
id=sl_svn151_96

><td class="source">uint64_t MurmurHash64A ( const void * key, int len, uint64_t seed )<br></td></tr
><tr
id=sl_svn151_97

><td class="source">{<br></td></tr
><tr
id=sl_svn151_98

><td class="source">  const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);<br></td></tr
><tr
id=sl_svn151_99

><td class="source">  const int r = 47;<br></td></tr
><tr
id=sl_svn151_100

><td class="source"><br></td></tr
><tr
id=sl_svn151_101

><td class="source">  uint64_t h = seed ^ (len * m);<br></td></tr
><tr
id=sl_svn151_102

><td class="source"><br></td></tr
><tr
id=sl_svn151_103

><td class="source">  const uint64_t * data = (const uint64_t *)key;<br></td></tr
><tr
id=sl_svn151_104

><td class="source">  const uint64_t * end = data + (len/8);<br></td></tr
><tr
id=sl_svn151_105

><td class="source"><br></td></tr
><tr
id=sl_svn151_106

><td class="source">  while(data != end)<br></td></tr
><tr
id=sl_svn151_107

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_108

><td class="source">    uint64_t k = *data++;<br></td></tr
><tr
id=sl_svn151_109

><td class="source"><br></td></tr
><tr
id=sl_svn151_110

><td class="source">    k *= m; <br></td></tr
><tr
id=sl_svn151_111

><td class="source">    k ^= k &gt;&gt; r; <br></td></tr
><tr
id=sl_svn151_112

><td class="source">    k *= m; <br></td></tr
><tr
id=sl_svn151_113

><td class="source">    <br></td></tr
><tr
id=sl_svn151_114

><td class="source">    h ^= k;<br></td></tr
><tr
id=sl_svn151_115

><td class="source">    h *= m; <br></td></tr
><tr
id=sl_svn151_116

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_117

><td class="source"><br></td></tr
><tr
id=sl_svn151_118

><td class="source">  const unsigned char * data2 = (const unsigned char*)data;<br></td></tr
><tr
id=sl_svn151_119

><td class="source"><br></td></tr
><tr
id=sl_svn151_120

><td class="source">  switch(len &amp; 7)<br></td></tr
><tr
id=sl_svn151_121

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_122

><td class="source">  case 7: h ^= uint64_t(data2[6]) &lt;&lt; 48;<br></td></tr
><tr
id=sl_svn151_123

><td class="source">  case 6: h ^= uint64_t(data2[5]) &lt;&lt; 40;<br></td></tr
><tr
id=sl_svn151_124

><td class="source">  case 5: h ^= uint64_t(data2[4]) &lt;&lt; 32;<br></td></tr
><tr
id=sl_svn151_125

><td class="source">  case 4: h ^= uint64_t(data2[3]) &lt;&lt; 24;<br></td></tr
><tr
id=sl_svn151_126

><td class="source">  case 3: h ^= uint64_t(data2[2]) &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_127

><td class="source">  case 2: h ^= uint64_t(data2[1]) &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_128

><td class="source">  case 1: h ^= uint64_t(data2[0]);<br></td></tr
><tr
id=sl_svn151_129

><td class="source">          h *= m;<br></td></tr
><tr
id=sl_svn151_130

><td class="source">  };<br></td></tr
><tr
id=sl_svn151_131

><td class="source"> <br></td></tr
><tr
id=sl_svn151_132

><td class="source">  h ^= h &gt;&gt; r;<br></td></tr
><tr
id=sl_svn151_133

><td class="source">  h *= m;<br></td></tr
><tr
id=sl_svn151_134

><td class="source">  h ^= h &gt;&gt; r;<br></td></tr
><tr
id=sl_svn151_135

><td class="source"><br></td></tr
><tr
id=sl_svn151_136

><td class="source">  return h;<br></td></tr
><tr
id=sl_svn151_137

><td class="source">} <br></td></tr
><tr
id=sl_svn151_138

><td class="source"><br></td></tr
><tr
id=sl_svn151_139

><td class="source"><br></td></tr
><tr
id=sl_svn151_140

><td class="source">// 64-bit hash for 32-bit platforms<br></td></tr
><tr
id=sl_svn151_141

><td class="source"><br></td></tr
><tr
id=sl_svn151_142

><td class="source">uint64_t MurmurHash64B ( const void * key, int len, uint64_t seed )<br></td></tr
><tr
id=sl_svn151_143

><td class="source">{<br></td></tr
><tr
id=sl_svn151_144

><td class="source">  const uint32_t m = 0x5bd1e995;<br></td></tr
><tr
id=sl_svn151_145

><td class="source">  const int r = 24;<br></td></tr
><tr
id=sl_svn151_146

><td class="source"><br></td></tr
><tr
id=sl_svn151_147

><td class="source">  uint32_t h1 = uint32_t(seed) ^ len;<br></td></tr
><tr
id=sl_svn151_148

><td class="source">  uint32_t h2 = uint32_t(seed &gt;&gt; 32);<br></td></tr
><tr
id=sl_svn151_149

><td class="source"><br></td></tr
><tr
id=sl_svn151_150

><td class="source">  const uint32_t * data = (const uint32_t *)key;<br></td></tr
><tr
id=sl_svn151_151

><td class="source"><br></td></tr
><tr
id=sl_svn151_152

><td class="source">  while(len &gt;= 8)<br></td></tr
><tr
id=sl_svn151_153

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_154

><td class="source">    uint32_t k1 = *data++;<br></td></tr
><tr
id=sl_svn151_155

><td class="source">    k1 *= m; k1 ^= k1 &gt;&gt; r; k1 *= m;<br></td></tr
><tr
id=sl_svn151_156

><td class="source">    h1 *= m; h1 ^= k1;<br></td></tr
><tr
id=sl_svn151_157

><td class="source">    len -= 4;<br></td></tr
><tr
id=sl_svn151_158

><td class="source"><br></td></tr
><tr
id=sl_svn151_159

><td class="source">    uint32_t k2 = *data++;<br></td></tr
><tr
id=sl_svn151_160

><td class="source">    k2 *= m; k2 ^= k2 &gt;&gt; r; k2 *= m;<br></td></tr
><tr
id=sl_svn151_161

><td class="source">    h2 *= m; h2 ^= k2;<br></td></tr
><tr
id=sl_svn151_162

><td class="source">    len -= 4;<br></td></tr
><tr
id=sl_svn151_163

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_164

><td class="source"><br></td></tr
><tr
id=sl_svn151_165

><td class="source">  if(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_166

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_167

><td class="source">    uint32_t k1 = *data++;<br></td></tr
><tr
id=sl_svn151_168

><td class="source">    k1 *= m; k1 ^= k1 &gt;&gt; r; k1 *= m;<br></td></tr
><tr
id=sl_svn151_169

><td class="source">    h1 *= m; h1 ^= k1;<br></td></tr
><tr
id=sl_svn151_170

><td class="source">    len -= 4;<br></td></tr
><tr
id=sl_svn151_171

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_172

><td class="source"><br></td></tr
><tr
id=sl_svn151_173

><td class="source">  switch(len)<br></td></tr
><tr
id=sl_svn151_174

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_175

><td class="source">  case 3: h2 ^= ((unsigned char*)data)[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_176

><td class="source">  case 2: h2 ^= ((unsigned char*)data)[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_177

><td class="source">  case 1: h2 ^= ((unsigned char*)data)[0];<br></td></tr
><tr
id=sl_svn151_178

><td class="source">      h2 *= m;<br></td></tr
><tr
id=sl_svn151_179

><td class="source">  };<br></td></tr
><tr
id=sl_svn151_180

><td class="source"><br></td></tr
><tr
id=sl_svn151_181

><td class="source">  h1 ^= h2 &gt;&gt; 18; h1 *= m;<br></td></tr
><tr
id=sl_svn151_182

><td class="source">  h2 ^= h1 &gt;&gt; 22; h2 *= m;<br></td></tr
><tr
id=sl_svn151_183

><td class="source">  h1 ^= h2 &gt;&gt; 17; h1 *= m;<br></td></tr
><tr
id=sl_svn151_184

><td class="source">  h2 ^= h1 &gt;&gt; 19; h2 *= m;<br></td></tr
><tr
id=sl_svn151_185

><td class="source"><br></td></tr
><tr
id=sl_svn151_186

><td class="source">  uint64_t h = h1;<br></td></tr
><tr
id=sl_svn151_187

><td class="source"><br></td></tr
><tr
id=sl_svn151_188

><td class="source">  h = (h &lt;&lt; 32) | h2;<br></td></tr
><tr
id=sl_svn151_189

><td class="source"><br></td></tr
><tr
id=sl_svn151_190

><td class="source">  return h;<br></td></tr
><tr
id=sl_svn151_191

><td class="source">} <br></td></tr
><tr
id=sl_svn151_192

><td class="source"><br></td></tr
><tr
id=sl_svn151_193

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_194

><td class="source">// MurmurHash2A, by Austin Appleby<br></td></tr
><tr
id=sl_svn151_195

><td class="source"><br></td></tr
><tr
id=sl_svn151_196

><td class="source">// This is a variant of MurmurHash2 modified to use the Merkle-Damgard <br></td></tr
><tr
id=sl_svn151_197

><td class="source">// construction. Bulk speed should be identical to Murmur2, small-key speed <br></td></tr
><tr
id=sl_svn151_198

><td class="source">// will be 10%-20% slower due to the added overhead at the end of the hash.<br></td></tr
><tr
id=sl_svn151_199

><td class="source"><br></td></tr
><tr
id=sl_svn151_200

><td class="source">// This variant fixes a minor issue where null keys were more likely to<br></td></tr
><tr
id=sl_svn151_201

><td class="source">// collide with each other than expected, and also makes the function<br></td></tr
><tr
id=sl_svn151_202

><td class="source">// more amenable to incremental implementations.<br></td></tr
><tr
id=sl_svn151_203

><td class="source"><br></td></tr
><tr
id=sl_svn151_204

><td class="source">#define mmix(h,k) { k *= m; k ^= k &gt;&gt; r; k *= m; h *= m; h ^= k; }<br></td></tr
><tr
id=sl_svn151_205

><td class="source"><br></td></tr
><tr
id=sl_svn151_206

><td class="source">uint32_t MurmurHash2A ( const void * key, int len, uint32_t seed )<br></td></tr
><tr
id=sl_svn151_207

><td class="source">{<br></td></tr
><tr
id=sl_svn151_208

><td class="source">  const uint32_t m = 0x5bd1e995;<br></td></tr
><tr
id=sl_svn151_209

><td class="source">  const int r = 24;<br></td></tr
><tr
id=sl_svn151_210

><td class="source">  uint32_t l = len;<br></td></tr
><tr
id=sl_svn151_211

><td class="source"><br></td></tr
><tr
id=sl_svn151_212

><td class="source">  const unsigned char * data = (const unsigned char *)key;<br></td></tr
><tr
id=sl_svn151_213

><td class="source"><br></td></tr
><tr
id=sl_svn151_214

><td class="source">  uint32_t h = seed;<br></td></tr
><tr
id=sl_svn151_215

><td class="source"><br></td></tr
><tr
id=sl_svn151_216

><td class="source">  while(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_217

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_218

><td class="source">    uint32_t k = *(uint32_t*)data;<br></td></tr
><tr
id=sl_svn151_219

><td class="source"><br></td></tr
><tr
id=sl_svn151_220

><td class="source">    mmix(h,k);<br></td></tr
><tr
id=sl_svn151_221

><td class="source"><br></td></tr
><tr
id=sl_svn151_222

><td class="source">    data += 4;<br></td></tr
><tr
id=sl_svn151_223

><td class="source">    len -= 4;<br></td></tr
><tr
id=sl_svn151_224

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_225

><td class="source"><br></td></tr
><tr
id=sl_svn151_226

><td class="source">  uint32_t t = 0;<br></td></tr
><tr
id=sl_svn151_227

><td class="source"><br></td></tr
><tr
id=sl_svn151_228

><td class="source">  switch(len)<br></td></tr
><tr
id=sl_svn151_229

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_230

><td class="source">  case 3: t ^= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_231

><td class="source">  case 2: t ^= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_232

><td class="source">  case 1: t ^= data[0];<br></td></tr
><tr
id=sl_svn151_233

><td class="source">  };<br></td></tr
><tr
id=sl_svn151_234

><td class="source"><br></td></tr
><tr
id=sl_svn151_235

><td class="source">  mmix(h,t);<br></td></tr
><tr
id=sl_svn151_236

><td class="source">  mmix(h,l);<br></td></tr
><tr
id=sl_svn151_237

><td class="source"><br></td></tr
><tr
id=sl_svn151_238

><td class="source">  h ^= h &gt;&gt; 13;<br></td></tr
><tr
id=sl_svn151_239

><td class="source">  h *= m;<br></td></tr
><tr
id=sl_svn151_240

><td class="source">  h ^= h &gt;&gt; 15;<br></td></tr
><tr
id=sl_svn151_241

><td class="source"><br></td></tr
><tr
id=sl_svn151_242

><td class="source">  return h;<br></td></tr
><tr
id=sl_svn151_243

><td class="source">}<br></td></tr
><tr
id=sl_svn151_244

><td class="source"><br></td></tr
><tr
id=sl_svn151_245

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_246

><td class="source">// CMurmurHash2A, by Austin Appleby<br></td></tr
><tr
id=sl_svn151_247

><td class="source"><br></td></tr
><tr
id=sl_svn151_248

><td class="source">// This is a sample implementation of MurmurHash2A designed to work <br></td></tr
><tr
id=sl_svn151_249

><td class="source">// incrementally.<br></td></tr
><tr
id=sl_svn151_250

><td class="source"><br></td></tr
><tr
id=sl_svn151_251

><td class="source">// Usage - <br></td></tr
><tr
id=sl_svn151_252

><td class="source"><br></td></tr
><tr
id=sl_svn151_253

><td class="source">// CMurmurHash2A hasher<br></td></tr
><tr
id=sl_svn151_254

><td class="source">// hasher.Begin(seed);<br></td></tr
><tr
id=sl_svn151_255

><td class="source">// hasher.Add(data1,size1);<br></td></tr
><tr
id=sl_svn151_256

><td class="source">// hasher.Add(data2,size2);<br></td></tr
><tr
id=sl_svn151_257

><td class="source">// ...<br></td></tr
><tr
id=sl_svn151_258

><td class="source">// hasher.Add(dataN,sizeN);<br></td></tr
><tr
id=sl_svn151_259

><td class="source">// uint32_t hash = hasher.End()<br></td></tr
><tr
id=sl_svn151_260

><td class="source"><br></td></tr
><tr
id=sl_svn151_261

><td class="source">class CMurmurHash2A<br></td></tr
><tr
id=sl_svn151_262

><td class="source">{<br></td></tr
><tr
id=sl_svn151_263

><td class="source">public:<br></td></tr
><tr
id=sl_svn151_264

><td class="source"><br></td></tr
><tr
id=sl_svn151_265

><td class="source">  void Begin ( uint32_t seed = 0 )<br></td></tr
><tr
id=sl_svn151_266

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_267

><td class="source">    m_hash  = seed;<br></td></tr
><tr
id=sl_svn151_268

><td class="source">    m_tail  = 0;<br></td></tr
><tr
id=sl_svn151_269

><td class="source">    m_count = 0;<br></td></tr
><tr
id=sl_svn151_270

><td class="source">    m_size  = 0;<br></td></tr
><tr
id=sl_svn151_271

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_272

><td class="source"><br></td></tr
><tr
id=sl_svn151_273

><td class="source">  void Add ( const unsigned char * data, int len )<br></td></tr
><tr
id=sl_svn151_274

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_275

><td class="source">    m_size += len;<br></td></tr
><tr
id=sl_svn151_276

><td class="source"><br></td></tr
><tr
id=sl_svn151_277

><td class="source">    MixTail(data,len);<br></td></tr
><tr
id=sl_svn151_278

><td class="source"><br></td></tr
><tr
id=sl_svn151_279

><td class="source">    while(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_280

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_281

><td class="source">      uint32_t k = *(uint32_t*)data;<br></td></tr
><tr
id=sl_svn151_282

><td class="source"><br></td></tr
><tr
id=sl_svn151_283

><td class="source">      mmix(m_hash,k);<br></td></tr
><tr
id=sl_svn151_284

><td class="source"><br></td></tr
><tr
id=sl_svn151_285

><td class="source">      data += 4;<br></td></tr
><tr
id=sl_svn151_286

><td class="source">      len -= 4;<br></td></tr
><tr
id=sl_svn151_287

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_288

><td class="source"><br></td></tr
><tr
id=sl_svn151_289

><td class="source">    MixTail(data,len);<br></td></tr
><tr
id=sl_svn151_290

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_291

><td class="source"><br></td></tr
><tr
id=sl_svn151_292

><td class="source">  uint32_t End ( void )<br></td></tr
><tr
id=sl_svn151_293

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_294

><td class="source">    mmix(m_hash,m_tail);<br></td></tr
><tr
id=sl_svn151_295

><td class="source">    mmix(m_hash,m_size);<br></td></tr
><tr
id=sl_svn151_296

><td class="source"><br></td></tr
><tr
id=sl_svn151_297

><td class="source">    m_hash ^= m_hash &gt;&gt; 13;<br></td></tr
><tr
id=sl_svn151_298

><td class="source">    m_hash *= m;<br></td></tr
><tr
id=sl_svn151_299

><td class="source">    m_hash ^= m_hash &gt;&gt; 15;<br></td></tr
><tr
id=sl_svn151_300

><td class="source"><br></td></tr
><tr
id=sl_svn151_301

><td class="source">    return m_hash;<br></td></tr
><tr
id=sl_svn151_302

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_303

><td class="source"><br></td></tr
><tr
id=sl_svn151_304

><td class="source">private:<br></td></tr
><tr
id=sl_svn151_305

><td class="source"><br></td></tr
><tr
id=sl_svn151_306

><td class="source">  static const uint32_t m = 0x5bd1e995;<br></td></tr
><tr
id=sl_svn151_307

><td class="source">  static const int r = 24;<br></td></tr
><tr
id=sl_svn151_308

><td class="source"><br></td></tr
><tr
id=sl_svn151_309

><td class="source">  void MixTail ( const unsigned char * &amp; data, int &amp; len )<br></td></tr
><tr
id=sl_svn151_310

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_311

><td class="source">    while( len &amp;&amp; ((len&lt;4) || m_count) )<br></td></tr
><tr
id=sl_svn151_312

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_313

><td class="source">      m_tail |= (*data++) &lt;&lt; (m_count * 8);<br></td></tr
><tr
id=sl_svn151_314

><td class="source"><br></td></tr
><tr
id=sl_svn151_315

><td class="source">      m_count++;<br></td></tr
><tr
id=sl_svn151_316

><td class="source">      len--;<br></td></tr
><tr
id=sl_svn151_317

><td class="source"><br></td></tr
><tr
id=sl_svn151_318

><td class="source">      if(m_count == 4)<br></td></tr
><tr
id=sl_svn151_319

><td class="source">      {<br></td></tr
><tr
id=sl_svn151_320

><td class="source">        mmix(m_hash,m_tail);<br></td></tr
><tr
id=sl_svn151_321

><td class="source">        m_tail = 0;<br></td></tr
><tr
id=sl_svn151_322

><td class="source">        m_count = 0;<br></td></tr
><tr
id=sl_svn151_323

><td class="source">      }<br></td></tr
><tr
id=sl_svn151_324

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_325

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_326

><td class="source"><br></td></tr
><tr
id=sl_svn151_327

><td class="source">  uint32_t m_hash;<br></td></tr
><tr
id=sl_svn151_328

><td class="source">  uint32_t m_tail;<br></td></tr
><tr
id=sl_svn151_329

><td class="source">  uint32_t m_count;<br></td></tr
><tr
id=sl_svn151_330

><td class="source">  uint32_t m_size;<br></td></tr
><tr
id=sl_svn151_331

><td class="source">};<br></td></tr
><tr
id=sl_svn151_332

><td class="source"><br></td></tr
><tr
id=sl_svn151_333

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_334

><td class="source">// MurmurHashNeutral2, by Austin Appleby<br></td></tr
><tr
id=sl_svn151_335

><td class="source"><br></td></tr
><tr
id=sl_svn151_336

><td class="source">// Same as MurmurHash2, but endian- and alignment-neutral.<br></td></tr
><tr
id=sl_svn151_337

><td class="source">// Half the speed though, alas.<br></td></tr
><tr
id=sl_svn151_338

><td class="source"><br></td></tr
><tr
id=sl_svn151_339

><td class="source">uint32_t MurmurHashNeutral2 ( const void * key, int len, uint32_t seed )<br></td></tr
><tr
id=sl_svn151_340

><td class="source">{<br></td></tr
><tr
id=sl_svn151_341

><td class="source">  const uint32_t m = 0x5bd1e995;<br></td></tr
><tr
id=sl_svn151_342

><td class="source">  const int r = 24;<br></td></tr
><tr
id=sl_svn151_343

><td class="source"><br></td></tr
><tr
id=sl_svn151_344

><td class="source">  uint32_t h = seed ^ len;<br></td></tr
><tr
id=sl_svn151_345

><td class="source"><br></td></tr
><tr
id=sl_svn151_346

><td class="source">  const unsigned char * data = (const unsigned char *)key;<br></td></tr
><tr
id=sl_svn151_347

><td class="source"><br></td></tr
><tr
id=sl_svn151_348

><td class="source">  while(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_349

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_350

><td class="source">    uint32_t k;<br></td></tr
><tr
id=sl_svn151_351

><td class="source"><br></td></tr
><tr
id=sl_svn151_352

><td class="source">    k  = data[0];<br></td></tr
><tr
id=sl_svn151_353

><td class="source">    k |= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_354

><td class="source">    k |= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_355

><td class="source">    k |= data[3] &lt;&lt; 24;<br></td></tr
><tr
id=sl_svn151_356

><td class="source"><br></td></tr
><tr
id=sl_svn151_357

><td class="source">    k *= m; <br></td></tr
><tr
id=sl_svn151_358

><td class="source">    k ^= k &gt;&gt; r; <br></td></tr
><tr
id=sl_svn151_359

><td class="source">    k *= m;<br></td></tr
><tr
id=sl_svn151_360

><td class="source"><br></td></tr
><tr
id=sl_svn151_361

><td class="source">    h *= m;<br></td></tr
><tr
id=sl_svn151_362

><td class="source">    h ^= k;<br></td></tr
><tr
id=sl_svn151_363

><td class="source"><br></td></tr
><tr
id=sl_svn151_364

><td class="source">    data += 4;<br></td></tr
><tr
id=sl_svn151_365

><td class="source">    len -= 4;<br></td></tr
><tr
id=sl_svn151_366

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_367

><td class="source">  <br></td></tr
><tr
id=sl_svn151_368

><td class="source">  switch(len)<br></td></tr
><tr
id=sl_svn151_369

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_370

><td class="source">  case 3: h ^= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_371

><td class="source">  case 2: h ^= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_372

><td class="source">  case 1: h ^= data[0];<br></td></tr
><tr
id=sl_svn151_373

><td class="source">          h *= m;<br></td></tr
><tr
id=sl_svn151_374

><td class="source">  };<br></td></tr
><tr
id=sl_svn151_375

><td class="source"><br></td></tr
><tr
id=sl_svn151_376

><td class="source">  h ^= h &gt;&gt; 13;<br></td></tr
><tr
id=sl_svn151_377

><td class="source">  h *= m;<br></td></tr
><tr
id=sl_svn151_378

><td class="source">  h ^= h &gt;&gt; 15;<br></td></tr
><tr
id=sl_svn151_379

><td class="source"><br></td></tr
><tr
id=sl_svn151_380

><td class="source">  return h;<br></td></tr
><tr
id=sl_svn151_381

><td class="source">} <br></td></tr
><tr
id=sl_svn151_382

><td class="source"><br></td></tr
><tr
id=sl_svn151_383

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_384

><td class="source">// MurmurHashAligned2, by Austin Appleby<br></td></tr
><tr
id=sl_svn151_385

><td class="source"><br></td></tr
><tr
id=sl_svn151_386

><td class="source">// Same algorithm as MurmurHash2, but only does aligned reads - should be safer<br></td></tr
><tr
id=sl_svn151_387

><td class="source">// on certain platforms. <br></td></tr
><tr
id=sl_svn151_388

><td class="source"><br></td></tr
><tr
id=sl_svn151_389

><td class="source">// Performance will be lower than MurmurHash2<br></td></tr
><tr
id=sl_svn151_390

><td class="source"><br></td></tr
><tr
id=sl_svn151_391

><td class="source">#define MIX(h,k,m) { k *= m; k ^= k &gt;&gt; r; k *= m; h *= m; h ^= k; }<br></td></tr
><tr
id=sl_svn151_392

><td class="source"><br></td></tr
><tr
id=sl_svn151_393

><td class="source"><br></td></tr
><tr
id=sl_svn151_394

><td class="source">uint32_t MurmurHashAligned2 ( const void * key, int len, uint32_t seed )<br></td></tr
><tr
id=sl_svn151_395

><td class="source">{<br></td></tr
><tr
id=sl_svn151_396

><td class="source">  const uint32_t m = 0x5bd1e995;<br></td></tr
><tr
id=sl_svn151_397

><td class="source">  const int r = 24;<br></td></tr
><tr
id=sl_svn151_398

><td class="source"><br></td></tr
><tr
id=sl_svn151_399

><td class="source">  const unsigned char * data = (const unsigned char *)key;<br></td></tr
><tr
id=sl_svn151_400

><td class="source"><br></td></tr
><tr
id=sl_svn151_401

><td class="source">  uint32_t h = seed ^ len;<br></td></tr
><tr
id=sl_svn151_402

><td class="source"><br></td></tr
><tr
id=sl_svn151_403

><td class="source">  int align = (uint64_t)data &amp; 3;<br></td></tr
><tr
id=sl_svn151_404

><td class="source"><br></td></tr
><tr
id=sl_svn151_405

><td class="source">  if(align &amp;&amp; (len &gt;= 4))<br></td></tr
><tr
id=sl_svn151_406

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_407

><td class="source">    // Pre-load the temp registers<br></td></tr
><tr
id=sl_svn151_408

><td class="source"><br></td></tr
><tr
id=sl_svn151_409

><td class="source">    uint32_t t = 0, d = 0;<br></td></tr
><tr
id=sl_svn151_410

><td class="source"><br></td></tr
><tr
id=sl_svn151_411

><td class="source">    switch(align)<br></td></tr
><tr
id=sl_svn151_412

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_413

><td class="source">      case 1: t |= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_414

><td class="source">      case 2: t |= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_415

><td class="source">      case 3: t |= data[0];<br></td></tr
><tr
id=sl_svn151_416

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_417

><td class="source"><br></td></tr
><tr
id=sl_svn151_418

><td class="source">    t &lt;&lt;= (8 * align);<br></td></tr
><tr
id=sl_svn151_419

><td class="source"><br></td></tr
><tr
id=sl_svn151_420

><td class="source">    data += 4-align;<br></td></tr
><tr
id=sl_svn151_421

><td class="source">    len -= 4-align;<br></td></tr
><tr
id=sl_svn151_422

><td class="source"><br></td></tr
><tr
id=sl_svn151_423

><td class="source">    int sl = 8 * (4-align);<br></td></tr
><tr
id=sl_svn151_424

><td class="source">    int sr = 8 * align;<br></td></tr
><tr
id=sl_svn151_425

><td class="source"><br></td></tr
><tr
id=sl_svn151_426

><td class="source">    // Mix<br></td></tr
><tr
id=sl_svn151_427

><td class="source"><br></td></tr
><tr
id=sl_svn151_428

><td class="source">    while(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_429

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_430

><td class="source">      d = *(uint32_t *)data;<br></td></tr
><tr
id=sl_svn151_431

><td class="source">      t = (t &gt;&gt; sr) | (d &lt;&lt; sl);<br></td></tr
><tr
id=sl_svn151_432

><td class="source"><br></td></tr
><tr
id=sl_svn151_433

><td class="source">      uint32_t k = t;<br></td></tr
><tr
id=sl_svn151_434

><td class="source"><br></td></tr
><tr
id=sl_svn151_435

><td class="source">      MIX(h,k,m);<br></td></tr
><tr
id=sl_svn151_436

><td class="source"><br></td></tr
><tr
id=sl_svn151_437

><td class="source">      t = d;<br></td></tr
><tr
id=sl_svn151_438

><td class="source"><br></td></tr
><tr
id=sl_svn151_439

><td class="source">      data += 4;<br></td></tr
><tr
id=sl_svn151_440

><td class="source">      len -= 4;<br></td></tr
><tr
id=sl_svn151_441

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_442

><td class="source"><br></td></tr
><tr
id=sl_svn151_443

><td class="source">    // Handle leftover data in temp registers<br></td></tr
><tr
id=sl_svn151_444

><td class="source"><br></td></tr
><tr
id=sl_svn151_445

><td class="source">    d = 0;<br></td></tr
><tr
id=sl_svn151_446

><td class="source"><br></td></tr
><tr
id=sl_svn151_447

><td class="source">    if(len &gt;= align)<br></td></tr
><tr
id=sl_svn151_448

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_449

><td class="source">      switch(align)<br></td></tr
><tr
id=sl_svn151_450

><td class="source">      {<br></td></tr
><tr
id=sl_svn151_451

><td class="source">      case 3: d |= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_452

><td class="source">      case 2: d |= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_453

><td class="source">      case 1: d |= data[0];<br></td></tr
><tr
id=sl_svn151_454

><td class="source">      }<br></td></tr
><tr
id=sl_svn151_455

><td class="source"><br></td></tr
><tr
id=sl_svn151_456

><td class="source">      uint32_t k = (t &gt;&gt; sr) | (d &lt;&lt; sl);<br></td></tr
><tr
id=sl_svn151_457

><td class="source">      MIX(h,k,m);<br></td></tr
><tr
id=sl_svn151_458

><td class="source"><br></td></tr
><tr
id=sl_svn151_459

><td class="source">      data += align;<br></td></tr
><tr
id=sl_svn151_460

><td class="source">      len -= align;<br></td></tr
><tr
id=sl_svn151_461

><td class="source"><br></td></tr
><tr
id=sl_svn151_462

><td class="source">      //----------<br></td></tr
><tr
id=sl_svn151_463

><td class="source">      // Handle tail bytes<br></td></tr
><tr
id=sl_svn151_464

><td class="source"><br></td></tr
><tr
id=sl_svn151_465

><td class="source">      switch(len)<br></td></tr
><tr
id=sl_svn151_466

><td class="source">      {<br></td></tr
><tr
id=sl_svn151_467

><td class="source">      case 3: h ^= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_468

><td class="source">      case 2: h ^= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_469

><td class="source">      case 1: h ^= data[0];<br></td></tr
><tr
id=sl_svn151_470

><td class="source">          h *= m;<br></td></tr
><tr
id=sl_svn151_471

><td class="source">      };<br></td></tr
><tr
id=sl_svn151_472

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_473

><td class="source">    else<br></td></tr
><tr
id=sl_svn151_474

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_475

><td class="source">      switch(len)<br></td></tr
><tr
id=sl_svn151_476

><td class="source">      {<br></td></tr
><tr
id=sl_svn151_477

><td class="source">      case 3: d |= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_478

><td class="source">      case 2: d |= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_479

><td class="source">      case 1: d |= data[0];<br></td></tr
><tr
id=sl_svn151_480

><td class="source">      case 0: h ^= (t &gt;&gt; sr) | (d &lt;&lt; sl);<br></td></tr
><tr
id=sl_svn151_481

><td class="source">          h *= m;<br></td></tr
><tr
id=sl_svn151_482

><td class="source">      }<br></td></tr
><tr
id=sl_svn151_483

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_484

><td class="source"><br></td></tr
><tr
id=sl_svn151_485

><td class="source">    h ^= h &gt;&gt; 13;<br></td></tr
><tr
id=sl_svn151_486

><td class="source">    h *= m;<br></td></tr
><tr
id=sl_svn151_487

><td class="source">    h ^= h &gt;&gt; 15;<br></td></tr
><tr
id=sl_svn151_488

><td class="source"><br></td></tr
><tr
id=sl_svn151_489

><td class="source">    return h;<br></td></tr
><tr
id=sl_svn151_490

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_491

><td class="source">  else<br></td></tr
><tr
id=sl_svn151_492

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_493

><td class="source">    while(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_494

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_495

><td class="source">      uint32_t k = *(uint32_t *)data;<br></td></tr
><tr
id=sl_svn151_496

><td class="source"><br></td></tr
><tr
id=sl_svn151_497

><td class="source">      MIX(h,k,m);<br></td></tr
><tr
id=sl_svn151_498

><td class="source"><br></td></tr
><tr
id=sl_svn151_499

><td class="source">      data += 4;<br></td></tr
><tr
id=sl_svn151_500

><td class="source">      len -= 4;<br></td></tr
><tr
id=sl_svn151_501

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_502

><td class="source"><br></td></tr
><tr
id=sl_svn151_503

><td class="source">    //----------<br></td></tr
><tr
id=sl_svn151_504

><td class="source">    // Handle tail bytes<br></td></tr
><tr
id=sl_svn151_505

><td class="source"><br></td></tr
><tr
id=sl_svn151_506

><td class="source">    switch(len)<br></td></tr
><tr
id=sl_svn151_507

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_508

><td class="source">    case 3: h ^= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_509

><td class="source">    case 2: h ^= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_510

><td class="source">    case 1: h ^= data[0];<br></td></tr
><tr
id=sl_svn151_511

><td class="source">        h *= m;<br></td></tr
><tr
id=sl_svn151_512

><td class="source">    };<br></td></tr
><tr
id=sl_svn151_513

><td class="source"><br></td></tr
><tr
id=sl_svn151_514

><td class="source">    h ^= h &gt;&gt; 13;<br></td></tr
><tr
id=sl_svn151_515

><td class="source">    h *= m;<br></td></tr
><tr
id=sl_svn151_516

><td class="source">    h ^= h &gt;&gt; 15;<br></td></tr
><tr
id=sl_svn151_517

><td class="source"><br></td></tr
><tr
id=sl_svn151_518

><td class="source">    return h;<br></td></tr
><tr
id=sl_svn151_519

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_520

><td class="source">}<br></td></tr
><tr
id=sl_svn151_521

><td class="source"><br></td></tr
><tr
id=sl_svn151_522

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_523

><td class="source"><br></td></tr
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
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=144&amp;format=side&amp;path=/trunk/MurmurHash2.cpp&amp;old_path=/trunk/MurmurHash2.cpp&amp;old=130">Diff</a>
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
 
 var selected_path = '/trunk/MurmurHash2.cpp';
 
 
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
 selected="selected"
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
 <a href="/p/smhasher/source/detail?spec=svn151&r=130">r130</a>
 by aappl...@google.com
 on Apr 8, 2011
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=130&amp;format=side&amp;path=/trunk/MurmurHash2.cpp&amp;old_path=/trunk/MurmurHash2.cpp&amp;old=129">Diff</a>
 <br>
 <pre class="ifOpened">Fix typos

</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <a class="ifClosed" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/plus.gif" ></a>
 <a class="ifOpened" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/minus.gif" ></a>
 <a href="/p/smhasher/source/detail?spec=svn151&r=129">r129</a>
 by aappl...@google.com
 on Apr 8, 2011
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=129&amp;format=side&amp;path=/trunk/MurmurHash2.cpp&amp;old_path=/trunk/MurmurHash2.cpp&amp;old=90">Diff</a>
 <br>
 <pre class="ifOpened">Remove dead files, make Murmur1/2/3
all have explicit public domain
licensing &amp; no external dependencies

</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <a class="ifClosed" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/plus.gif" ></a>
 <a class="ifOpened" onclick="return _toggleHidden(this)"><img src="https://ssl.gstatic.com/codesite/ph/images/minus.gif" ></a>
 <a href="/p/smhasher/source/detail?spec=svn151&r=90">r90</a>
 by tanjent
 on Mar 19, 2011
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=90&amp;format=side&amp;path=/trunk/MurmurHash2.cpp&amp;old_path=/trunk/MurmurHash2.cpp&amp;old=89">Diff</a>
 <br>
 <pre class="ifOpened">Add startup self-test
Remove randhash (will fail self-test)
Remove QuickBrownFox (replaced by
VerificationTest)
De-tabulate all files</pre>
 </div>
 
 
 <a href="/p/smhasher/source/list?path=/trunk/MurmurHash2.cpp&start=144">All revisions of this file</a>
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
 
 <div>Size: 9856 bytes,
 523 lines</div>
 
 <div><a href="//smhasher.googlecode.com/svn/trunk/MurmurHash2.cpp">View raw file</a></div>
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
 var paths = {'svn151': '/trunk/MurmurHash2.cpp'}
 codereviews = CR_controller.setup(
 {"relativeBaseUrl": "", "domainName": null, "assetHostPath": "https://ssl.gstatic.com/codesite/ph", "assetVersionPath": "https://ssl.gstatic.com/codesite/ph/11104804043454007890", "profileUrl": "/u/109814223914636253922/", "projectHomeUrl": "/p/smhasher", "token": "M7iXhx73gCSrPjeUFEQWUu3LzZI:1390098585148", "projectName": "smhasher", "loggedInUserEmail": "alanparsonsproject28@gmail.com"}, '', 'svn151', paths,
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

