



<!DOCTYPE html>
<html>
<head>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link rel="icon" type="image/vnd.microsoft.icon" href="https://ssl.gstatic.com/codesite/ph/images/phosting.ico">
 
 
 <script type="text/javascript">
 
 
 
 
 var codesite_token = "L91bZiU_w2k9yGTR3-VYQll857Q:1390098593502";
 
 
 var CS_env = {"projectHomeUrl": "/p/smhasher", "loggedInUserEmail": "alanparsonsproject28@gmail.com", "token": "L91bZiU_w2k9yGTR3-VYQll857Q:1390098593502", "domainName": null, "profileUrl": "/u/109814223914636253922/", "projectName": "smhasher", "assetVersionPath": "https://ssl.gstatic.com/codesite/ph/11104804043454007890", "relativeBaseUrl": "", "assetHostPath": "https://ssl.gstatic.com/codesite/ph"};
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
 
 
 <title>MurmurHash1.cpp - 
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
 | <a href="https://www.google.com/accounts/Logout?continue=https%3A%2F%2Fcode.google.com%2Fp%2Fsmhasher%2Fsource%2Fbrowse%2Ftrunk%2FMurmurHash1.cpp" 
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
 <span id="crumb_links" class="ifClosed"><a href="/p/smhasher/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span>MurmurHash1.cpp</span>
 
 


 </td>
 
 
 <td nowrap="nowrap" width="33%" align="center">
 <a href="/p/smhasher/source/browse/trunk/MurmurHash1.cpp?edit=1"
 ><img src="https://ssl.gstatic.com/codesite/ph/images/pencil-y14.png"
 class="edit_icon">Edit file</a>
 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper">
 <ul class="leftside">
 
 <li><a href="/p/smhasher/source/browse/trunk/MurmurHash1.cpp?r=129" title="Previous">&lsaquo;r129</a></li>
 
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

><td class="source">// MurmurHash was written by Austin Appleby, and is placed in the public<br></td></tr
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

><td class="source">#include &quot;MurmurHash1.h&quot;<br></td></tr
><tr
id=sl_svn151_17

><td class="source"><br></td></tr
><tr
id=sl_svn151_18

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_19

><td class="source"><br></td></tr
><tr
id=sl_svn151_20

><td class="source">uint32_t MurmurHash1 ( const void * key, int len, uint32_t seed )<br></td></tr
><tr
id=sl_svn151_21

><td class="source">{<br></td></tr
><tr
id=sl_svn151_22

><td class="source">  const unsigned int m = 0xc6a4a793;<br></td></tr
><tr
id=sl_svn151_23

><td class="source"><br></td></tr
><tr
id=sl_svn151_24

><td class="source">  const int r = 16;<br></td></tr
><tr
id=sl_svn151_25

><td class="source"><br></td></tr
><tr
id=sl_svn151_26

><td class="source">  unsigned int h = seed ^ (len * m);<br></td></tr
><tr
id=sl_svn151_27

><td class="source"><br></td></tr
><tr
id=sl_svn151_28

><td class="source">  //----------<br></td></tr
><tr
id=sl_svn151_29

><td class="source">  <br></td></tr
><tr
id=sl_svn151_30

><td class="source">  const unsigned char * data = (const unsigned char *)key;<br></td></tr
><tr
id=sl_svn151_31

><td class="source"><br></td></tr
><tr
id=sl_svn151_32

><td class="source">  while(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_33

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_34

><td class="source">    unsigned int k = *(unsigned int *)data;<br></td></tr
><tr
id=sl_svn151_35

><td class="source"><br></td></tr
><tr
id=sl_svn151_36

><td class="source">    h += k;<br></td></tr
><tr
id=sl_svn151_37

><td class="source">    h *= m;<br></td></tr
><tr
id=sl_svn151_38

><td class="source">    h ^= h &gt;&gt; 16;<br></td></tr
><tr
id=sl_svn151_39

><td class="source"><br></td></tr
><tr
id=sl_svn151_40

><td class="source">    data += 4;<br></td></tr
><tr
id=sl_svn151_41

><td class="source">    len -= 4;<br></td></tr
><tr
id=sl_svn151_42

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_43

><td class="source">  <br></td></tr
><tr
id=sl_svn151_44

><td class="source">  //----------<br></td></tr
><tr
id=sl_svn151_45

><td class="source">  <br></td></tr
><tr
id=sl_svn151_46

><td class="source">  switch(len)<br></td></tr
><tr
id=sl_svn151_47

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_48

><td class="source">  case 3:<br></td></tr
><tr
id=sl_svn151_49

><td class="source">    h += data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_50

><td class="source">  case 2:<br></td></tr
><tr
id=sl_svn151_51

><td class="source">    h += data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_52

><td class="source">  case 1:<br></td></tr
><tr
id=sl_svn151_53

><td class="source">    h += data[0];<br></td></tr
><tr
id=sl_svn151_54

><td class="source">    h *= m;<br></td></tr
><tr
id=sl_svn151_55

><td class="source">    h ^= h &gt;&gt; r;<br></td></tr
><tr
id=sl_svn151_56

><td class="source">  };<br></td></tr
><tr
id=sl_svn151_57

><td class="source"> <br></td></tr
><tr
id=sl_svn151_58

><td class="source">  //----------<br></td></tr
><tr
id=sl_svn151_59

><td class="source"><br></td></tr
><tr
id=sl_svn151_60

><td class="source">  h *= m;<br></td></tr
><tr
id=sl_svn151_61

><td class="source">  h ^= h &gt;&gt; 10;<br></td></tr
><tr
id=sl_svn151_62

><td class="source">  h *= m;<br></td></tr
><tr
id=sl_svn151_63

><td class="source">  h ^= h &gt;&gt; 17;<br></td></tr
><tr
id=sl_svn151_64

><td class="source"><br></td></tr
><tr
id=sl_svn151_65

><td class="source">  return h;<br></td></tr
><tr
id=sl_svn151_66

><td class="source">} <br></td></tr
><tr
id=sl_svn151_67

><td class="source"><br></td></tr
><tr
id=sl_svn151_68

><td class="source">//-----------------------------------------------------------------------------<br></td></tr
><tr
id=sl_svn151_69

><td class="source">// MurmurHash1Aligned, by Austin Appleby<br></td></tr
><tr
id=sl_svn151_70

><td class="source"><br></td></tr
><tr
id=sl_svn151_71

><td class="source">// Same algorithm as MurmurHash1, but only does aligned reads - should be safer<br></td></tr
><tr
id=sl_svn151_72

><td class="source">// on certain platforms. <br></td></tr
><tr
id=sl_svn151_73

><td class="source"><br></td></tr
><tr
id=sl_svn151_74

><td class="source">// Performance should be equal to or better than the simple version.<br></td></tr
><tr
id=sl_svn151_75

><td class="source"><br></td></tr
><tr
id=sl_svn151_76

><td class="source">unsigned int MurmurHash1Aligned ( const void * key, int len, unsigned int seed )<br></td></tr
><tr
id=sl_svn151_77

><td class="source">{<br></td></tr
><tr
id=sl_svn151_78

><td class="source">  const unsigned int m = 0xc6a4a793;<br></td></tr
><tr
id=sl_svn151_79

><td class="source">  const int r = 16;<br></td></tr
><tr
id=sl_svn151_80

><td class="source"><br></td></tr
><tr
id=sl_svn151_81

><td class="source">  const unsigned char * data = (const unsigned char *)key;<br></td></tr
><tr
id=sl_svn151_82

><td class="source"><br></td></tr
><tr
id=sl_svn151_83

><td class="source">  unsigned int h = seed ^ (len * m);<br></td></tr
><tr
id=sl_svn151_84

><td class="source"><br></td></tr
><tr
id=sl_svn151_85

><td class="source">  int align = (uint64_t)data &amp; 3;<br></td></tr
><tr
id=sl_svn151_86

><td class="source"><br></td></tr
><tr
id=sl_svn151_87

><td class="source">  if(align &amp;&amp; (len &gt;= 4))<br></td></tr
><tr
id=sl_svn151_88

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_89

><td class="source">    // Pre-load the temp registers<br></td></tr
><tr
id=sl_svn151_90

><td class="source"><br></td></tr
><tr
id=sl_svn151_91

><td class="source">    unsigned int t = 0, d = 0;<br></td></tr
><tr
id=sl_svn151_92

><td class="source"><br></td></tr
><tr
id=sl_svn151_93

><td class="source">    switch(align)<br></td></tr
><tr
id=sl_svn151_94

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_95

><td class="source">      case 1: t |= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_96

><td class="source">      case 2: t |= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_97

><td class="source">      case 3: t |= data[0];<br></td></tr
><tr
id=sl_svn151_98

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_99

><td class="source"><br></td></tr
><tr
id=sl_svn151_100

><td class="source">    t &lt;&lt;= (8 * align);<br></td></tr
><tr
id=sl_svn151_101

><td class="source"><br></td></tr
><tr
id=sl_svn151_102

><td class="source">    data += 4-align;<br></td></tr
><tr
id=sl_svn151_103

><td class="source">    len -= 4-align;<br></td></tr
><tr
id=sl_svn151_104

><td class="source"><br></td></tr
><tr
id=sl_svn151_105

><td class="source">    int sl = 8 * (4-align);<br></td></tr
><tr
id=sl_svn151_106

><td class="source">    int sr = 8 * align;<br></td></tr
><tr
id=sl_svn151_107

><td class="source"><br></td></tr
><tr
id=sl_svn151_108

><td class="source">    // Mix<br></td></tr
><tr
id=sl_svn151_109

><td class="source"><br></td></tr
><tr
id=sl_svn151_110

><td class="source">    while(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_111

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_112

><td class="source">      d = *(unsigned int *)data;<br></td></tr
><tr
id=sl_svn151_113

><td class="source">      t = (t &gt;&gt; sr) | (d &lt;&lt; sl);<br></td></tr
><tr
id=sl_svn151_114

><td class="source">      h += t;<br></td></tr
><tr
id=sl_svn151_115

><td class="source">      h *= m;<br></td></tr
><tr
id=sl_svn151_116

><td class="source">      h ^= h &gt;&gt; r;<br></td></tr
><tr
id=sl_svn151_117

><td class="source">      t = d;<br></td></tr
><tr
id=sl_svn151_118

><td class="source"><br></td></tr
><tr
id=sl_svn151_119

><td class="source">      data += 4;<br></td></tr
><tr
id=sl_svn151_120

><td class="source">      len -= 4;<br></td></tr
><tr
id=sl_svn151_121

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_122

><td class="source"><br></td></tr
><tr
id=sl_svn151_123

><td class="source">    // Handle leftover data in temp registers<br></td></tr
><tr
id=sl_svn151_124

><td class="source"><br></td></tr
><tr
id=sl_svn151_125

><td class="source">    int pack = len &lt; align ? len : align;<br></td></tr
><tr
id=sl_svn151_126

><td class="source"><br></td></tr
><tr
id=sl_svn151_127

><td class="source">    d = 0;<br></td></tr
><tr
id=sl_svn151_128

><td class="source"><br></td></tr
><tr
id=sl_svn151_129

><td class="source">    switch(pack)<br></td></tr
><tr
id=sl_svn151_130

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_131

><td class="source">    case 3: d |= data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_132

><td class="source">    case 2: d |= data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_133

><td class="source">    case 1: d |= data[0];<br></td></tr
><tr
id=sl_svn151_134

><td class="source">    case 0: h += (t &gt;&gt; sr) | (d &lt;&lt; sl);<br></td></tr
><tr
id=sl_svn151_135

><td class="source">        h *= m;<br></td></tr
><tr
id=sl_svn151_136

><td class="source">        h ^= h &gt;&gt; r;<br></td></tr
><tr
id=sl_svn151_137

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_138

><td class="source"><br></td></tr
><tr
id=sl_svn151_139

><td class="source">    data += pack;<br></td></tr
><tr
id=sl_svn151_140

><td class="source">    len -= pack;<br></td></tr
><tr
id=sl_svn151_141

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_142

><td class="source">  else<br></td></tr
><tr
id=sl_svn151_143

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_144

><td class="source">    while(len &gt;= 4)<br></td></tr
><tr
id=sl_svn151_145

><td class="source">    {<br></td></tr
><tr
id=sl_svn151_146

><td class="source">      h += *(unsigned int *)data;<br></td></tr
><tr
id=sl_svn151_147

><td class="source">      h *= m;<br></td></tr
><tr
id=sl_svn151_148

><td class="source">      h ^= h &gt;&gt; r;<br></td></tr
><tr
id=sl_svn151_149

><td class="source"><br></td></tr
><tr
id=sl_svn151_150

><td class="source">      data += 4;<br></td></tr
><tr
id=sl_svn151_151

><td class="source">      len -= 4;<br></td></tr
><tr
id=sl_svn151_152

><td class="source">    }<br></td></tr
><tr
id=sl_svn151_153

><td class="source">  }<br></td></tr
><tr
id=sl_svn151_154

><td class="source"><br></td></tr
><tr
id=sl_svn151_155

><td class="source">  //----------<br></td></tr
><tr
id=sl_svn151_156

><td class="source">  // Handle tail bytes<br></td></tr
><tr
id=sl_svn151_157

><td class="source"><br></td></tr
><tr
id=sl_svn151_158

><td class="source">  switch(len)<br></td></tr
><tr
id=sl_svn151_159

><td class="source">  {<br></td></tr
><tr
id=sl_svn151_160

><td class="source">  case 3: h += data[2] &lt;&lt; 16;<br></td></tr
><tr
id=sl_svn151_161

><td class="source">  case 2: h += data[1] &lt;&lt; 8;<br></td></tr
><tr
id=sl_svn151_162

><td class="source">  case 1: h += data[0];<br></td></tr
><tr
id=sl_svn151_163

><td class="source">      h *= m;<br></td></tr
><tr
id=sl_svn151_164

><td class="source">      h ^= h &gt;&gt; r;<br></td></tr
><tr
id=sl_svn151_165

><td class="source">  };<br></td></tr
><tr
id=sl_svn151_166

><td class="source"><br></td></tr
><tr
id=sl_svn151_167

><td class="source">  h *= m;<br></td></tr
><tr
id=sl_svn151_168

><td class="source">  h ^= h &gt;&gt; 10;<br></td></tr
><tr
id=sl_svn151_169

><td class="source">  h *= m;<br></td></tr
><tr
id=sl_svn151_170

><td class="source">  h ^= h &gt;&gt; 17;<br></td></tr
><tr
id=sl_svn151_171

><td class="source"><br></td></tr
><tr
id=sl_svn151_172

><td class="source">  return h;<br></td></tr
><tr
id=sl_svn151_173

><td class="source">}<br></td></tr
><tr
id=sl_svn151_174

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
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=144&amp;format=side&amp;path=/trunk/MurmurHash1.cpp&amp;old_path=/trunk/MurmurHash1.cpp&amp;old=129">Diff</a>
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
 
 var selected_path = '/trunk/MurmurHash1.cpp';
 
 
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
 selected="selected"
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
 <a href="/p/smhasher/source/detail?spec=svn151&r=129">r129</a>
 by aappl...@google.com
 on Apr 8, 2011
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=129&amp;format=side&amp;path=/trunk/MurmurHash1.cpp&amp;old_path=/trunk/MurmurHash1.cpp&amp;old=90">Diff</a>
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
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=90&amp;format=side&amp;path=/trunk/MurmurHash1.cpp&amp;old_path=/trunk/MurmurHash1.cpp&amp;old=89">Diff</a>
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
 <a href="/p/smhasher/source/detail?spec=svn151&r=89">r89</a>
 by McKay.Davis
 on Mar 19, 2011
 &nbsp; <a href="/p/smhasher/source/diff?spec=svn151&r=89&amp;format=side&amp;path=/trunk/MurmurHash1.cpp&amp;old_path=/trunk/MurmurHash1.cpp&amp;old=2">Diff</a>
 <br>
 <pre class="ifOpened">Fix x86_64 gcc 4.4.1 build errors:

/smhasher/<a title="" href="/p/smhasher/wiki/MurmurHash1">MurmurHash1</a>.cpp: In function
‘unsigned int MurmurHash1Aligned(const
void*, int, unsigned int)’:
...</pre>
 </div>
 
 
 <a href="/p/smhasher/source/list?path=/trunk/MurmurHash1.cpp&start=144">All revisions of this file</a>
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
 
 <div>Size: 3160 bytes,
 174 lines</div>
 
 <div><a href="//smhasher.googlecode.com/svn/trunk/MurmurHash1.cpp">View raw file</a></div>
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
 var paths = {'svn151': '/trunk/MurmurHash1.cpp'}
 codereviews = CR_controller.setup(
 {"projectHomeUrl": "/p/smhasher", "loggedInUserEmail": "alanparsonsproject28@gmail.com", "token": "L91bZiU_w2k9yGTR3-VYQll857Q:1390098593502", "domainName": null, "profileUrl": "/u/109814223914636253922/", "projectName": "smhasher", "assetVersionPath": "https://ssl.gstatic.com/codesite/ph/11104804043454007890", "relativeBaseUrl": "", "assetHostPath": "https://ssl.gstatic.com/codesite/ph"}, '', 'svn151', paths,
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

