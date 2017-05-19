'use strict';(function(g){function p(a){"string"!==typeof a&&(a=String(a));if(/[^a-z0-9\-#$%&'*+.\^_`|~]/i.test(a))throw new h("Invalid character in header field name");return a.toLowerCase()}function v(a){"string"!==typeof a&&(a=String(a));var b,d;for(b=0;b<a.length;b++){var c=a.charCodeAt(b);if(9!==c&&10!==c&&13!==c&&32!==c)break}for(d=a.length-1;d>b&&(c=a.charCodeAt(d),9===c||10===c||13===c||32===c);d--);a=a.substring(b,d+1);for(b=0;b<a.length;b++)if(c=a.charCodeAt(b),256<=c||0===c||10===c||13===
c)throw new h("Invalid character in header field value");return a}function e(a){this.map=new q;if(void 0!==a){if(null===a||"object"!==typeof a)throw new h("Constructing Headers with invalid parameters");a instanceof e?a.forEach(function(a,d){this.append(d,a)},this):m.isArray(a)?a.forEach(function(a){if(2!==a.length)throw new h("Constructing Headers with invalid parameters");this.append(a[0],a[1])},this):Object.getOwnPropertyNames(a).forEach(function(b){this.append(b,a[b])},this)}}function t(a){if(a.bodyUsed)return Promise.reject(new h("Already read"));
a.bodyUsed=!0}function w(a){return new Promise(function(b,d){a.onload=function(){b(a.result)};a.onerror=function(){d(a.error)}})}function z(a){var b=new FileReader,d=w(b);b.readAsArrayBuffer(a);return d}function A(a){a=new Uint8Array(a);for(var b=new m(a.length),d=0;d<a.length;d++)b[d]=String.fromCharCode(a[d]);return b.join("")}function x(a){if(a.slice)return a.slice(0);var b=new Uint8Array(a.byteLength);b.set(new Uint8Array(a));return b.buffer}function y(){this.bodyUsed=!1;this._initBody=function(a){if(this._bodyInit=
a)if("string"===typeof a)this._bodyText=a;else if(k.blob&&Blob.prototype.isPrototypeOf(a))this._bodyBlob=a;else if(k.formData&&FormData.prototype.isPrototypeOf(a))this._bodyFormData=a;else if(k.searchParams&&URLSearchParams.prototype.isPrototypeOf(a))this._bodyText=a.toString();else if(k.arrayBuffer&&k.blob&&B(a))this._bodyArrayBuffer=x(a.buffer),this._bodyInit=new Blob([this._bodyArrayBuffer]);else if(k.arrayBuffer&&(ArrayBuffer.prototype.isPrototypeOf(a)||C(a)))this._bodyArrayBuffer=x(a);else throw new u("unsupported BodyInit type");
else this._bodyText="";this.headers.get("content-type")||("string"===typeof a?this.headers.set("content-type","text/plain;charset=UTF-8"):this._bodyBlob&&this._bodyBlob.type?this.headers.set("content-type",this._bodyBlob.type):k.searchParams&&URLSearchParams.prototype.isPrototypeOf(a)&&this.headers.set("content-type","application/x-www-form-urlencoded;charset=UTF-8"))};k.blob&&(this.blob=function(){var a=t(this);if(a)return a;if(this._bodyBlob)return Promise.resolve(this._bodyBlob);if(this._bodyArrayBuffer)return Promise.resolve(new Blob([this._bodyArrayBuffer]));
if(this._bodyFormData)throw new u("could not read FormData body as blob");return Promise.resolve(new Blob([this._bodyText]))},this.arrayBuffer=function(){return this._bodyArrayBuffer?t(this)||Promise.resolve(this._bodyArrayBuffer):this.blob().then(z)});this.text=function(){var a=t(this);if(a)return a;if(this._bodyBlob){var a=this._bodyBlob,b=new FileReader,d=w(b);b.readAsText(a);return d}if(this._bodyArrayBuffer)return Promise.resolve(A(this._bodyArrayBuffer));if(this._bodyFormData)throw new u("could not read FormData body as text");
return Promise.resolve(this._bodyText)};k.formData&&(this.formData=function(){return this.text().then(D)});this.json=function(){return this.text().then(JSON.parse)};return this}function n(a,b){b=b||{};var d=b.body;if(a instanceof n){if(a.bodyUsed)throw new h("Already read");this.url=a.url;this.credentials=a.credentials;b.headers||(this.headers=new e(a.headers));this.method=a.method;this.mode=a.mode;d||null==a._bodyInit||(d=a._bodyInit,a.bodyUsed=!0)}else this.url=String(a);this.credentials=b.credentials||
this.credentials||"omit";if(b.headers||!this.headers)this.headers=new e(b.headers);a=b.method||this.method||"GET";var c=a.toUpperCase();this.method=-1<E.indexOf(c)?c:a;this.mode=b.mode||this.mode||null;this.referrer=null;if(("GET"===this.method||"HEAD"===this.method)&&d)throw new h("Body not allowed for GET or HEAD requests");this._initBody(d)}function D(a){var b=new FormData;a.trim().split("&").forEach(function(a){if(a){var c=a.split("=");a=c.shift().replace(/\+/g," ");c=c.join("=").replace(/\+/g,
" ");b.append(decodeURIComponent(a),decodeURIComponent(c))}});return b}function F(a){var b=new e;a.replace(/\r?\n[\t ]+/g," ").split(/\r?\n/).forEach(function(a){var c=a.split(":");if(a=c.shift().trim())c=c.join(":").trim(),b.append(a,c)});return b}function l(a,b){b||(b={});this.type="default";this.status="status"in b?b.status:200;this.ok=200<=this.status&&300>this.status;this.statusText="statusText"in b?b.statusText:"OK";this.headers=new e(b.headers);this.url=b.url||"";this._initBody(a)}if(!g.fetch){var m=
g.Array,u=g.Error,q=g.Map,G=g.RangeError,h=g.TypeError,r;if(r="FileReader"in g&&"Blob"in g)try{new Blob,r=!0}catch(a){r=!1}var k={searchParams:"URLSearchParams"in g,blob:r,formData:"FormData"in g,arrayBuffer:"ArrayBuffer"in g};if(k.arrayBuffer){var H="[object Int8Array];[object Uint8Array];[object Uint8ClampedArray];[object Int16Array];[object Uint16Array];[object Int32Array];[object Uint32Array];[object Float32Array];[object Float64Array]".split(";");var B=function(a){return a&&DataView.prototype.isPrototypeOf(a)};
var C=ArrayBuffer.isView||function(a){return a&&-1<H.indexOf(Object.prototype.toString.call(a))}}e.prototype.append=function(a,b){if(2!==arguments.length)throw h("Invalid parameters to append");a=p(a);b=v(b);this.map.has(a)?this.map.set(a,this.map.get(a)+", "+b):this.map.set(a,b)};e.prototype["delete"]=function(a){if(1!==arguments.length)throw h("Invalid parameters to delete");this.map.delete(p(a))};e.prototype.get=function(a){if(1!==arguments.length)throw h("Invalid parameters to get");a=p(a);var b=
this.map.get(a);return void 0!==b?b:null};e.prototype.has=function(a){if(1!==arguments.length)throw h("Invalid parameters to has");return this.map.has(p(a))};e.prototype.set=function(a,b){if(2!==arguments.length)throw h("Invalid parameters to set");this.map.set(p(a),v(b))};e.prototype.forEach=function(a,b){var d=this;m.from(this.map.entries()).sort().forEach(function(c){a.call(b,c[1],c[0],d)})};e.prototype.keys=function(){return(new q(m.from(this.map.entries()).sort())).keys()};e.prototype.values=
function(){return(new q(m.from(this.map.entries()).sort())).values()};e.prototype.entries=function(){return(new q(m.from(this.map.entries()).sort())).entries()};e.prototype[Symbol.iterator]=e.prototype.entries;var E="DELETE GET HEAD OPTIONS POST PUT".split(" ");n.prototype.clone=function(){return new n(this,{body:this._bodyInit})};y.call(n.prototype);y.call(l.prototype);l.prototype.clone=function(){return new l(this._bodyInit,{status:this.status,statusText:this.statusText,headers:new e(this.headers),
url:this.url})};l.error=function(){var a=new l(null,{status:0,statusText:""});a.type="error";return a};var I=[301,302,303,307,308];l.redirect=function(a,b){if(-1===I.indexOf(b))throw new G("Invalid status code");return new l(null,{status:b,headers:{location:a}})};g.Headers=e;g.Request=n;g.Response=l;g.fetch=function(a,b){return new Promise(function(d,c){var e=new n(a,b),f=new XMLHttpRequest;f.onload=function(){var a={status:f.status,statusText:f.statusText,headers:F(f.getAllResponseHeaders()||"")};
a.url="responseURL"in f?f.responseURL:a.headers.get("X-Request-URL");d(new l("response"in f?f.response:f.responseText,a))};f.onerror=function(){c(new h("Network request failed"))};f.ontimeout=function(){c(new h("Network request failed"))};f.open(e.method,e.url,!0);"include"===e.credentials&&(f.withCredentials=!0);"responseType"in f&&k.blob&&(f.responseType="blob");e.headers.forEach(function(a,b){f.setRequestHeader(b,a)});f.send("undefined"===typeof e._bodyInit?null:e._bodyInit)})};g.fetch.polyfill=
!0}})(this);