function x(){}const X=t=>t;function pt(t,e){for(const n in e)t[n]=e[n];return t}function Y(t){return t()}function K(){return Object.create(null)}function b(t){t.forEach(Y)}function F(t){return typeof t=="function"}function zt(t,e){return t!=t?e==e:t!==e||t&&typeof t=="object"||typeof t=="function"}let T;function Ft(t,e){return T||(T=document.createElement("a")),T.href=e,t===T.href}function yt(t){return Object.keys(t).length===0}function gt(t,...e){if(t==null)return x;const n=t.subscribe(...e);return n.unsubscribe?()=>n.unsubscribe():n}function Gt(t,e,n){t.$$.on_destroy.push(gt(e,n))}function It(t,e,n,i){if(t){const s=Z(t,e,n,i);return t[0](s)}}function Z(t,e,n,i){return t[1]&&i?pt(n.ctx.slice(),t[1](i(e))):n.ctx}function Wt(t,e,n,i){if(t[2]&&i){const s=t[2](i(n));if(e.dirty===void 0)return s;if(typeof s=="object"){const l=[],r=Math.max(e.dirty.length,s.length);for(let o=0;o<r;o+=1)l[o]=e.dirty[o]|s[o];return l}return e.dirty|s}return e.dirty}function Jt(t,e,n,i,s,l){if(s){const r=Z(e,n,i,l);t.p(r,s)}}function Kt(t){if(t.ctx.length>32){const e=[],n=t.ctx.length/32;for(let i=0;i<n;i++)e[i]=-1;return e}return-1}function Qt(t){const e={};for(const n in t)n[0]!=="$"&&(e[n]=t[n]);return e}function Ut(t,e){const n={};e=new Set(e);for(const i in t)!e.has(i)&&i[0]!=="$"&&(n[i]=t[i]);return n}function Vt(t){const e={};for(const n in t)e[n]=!0;return e}function Xt(t){return t==null?"":t}function Yt(t,e,n){return t.set(n),e}const tt=typeof window!="undefined";let et=tt?()=>window.performance.now():()=>Date.now(),G=tt?t=>requestAnimationFrame(t):x;const g=new Set;function nt(t){g.forEach(e=>{e.c(t)||(g.delete(e),e.f())}),g.size!==0&&G(nt)}function it(t){let e;return g.size===0&&G(nt),{promise:new Promise(n=>{g.add(e={c:t,f:n})}),abort(){g.delete(e)}}}let L=!1;function xt(){L=!0}function bt(){L=!1}function $t(t,e,n,i){for(;t<e;){const s=t+(e-t>>1);n(s)<=i?t=s+1:e=s}return t}function wt(t){if(t.hydrate_init)return;t.hydrate_init=!0;let e=t.childNodes;if(t.nodeName==="HEAD"){const c=[];for(let u=0;u<e.length;u++){const f=e[u];f.claim_order!==void 0&&c.push(f)}e=c}const n=new Int32Array(e.length+1),i=new Int32Array(e.length);n[0]=-1;let s=0;for(let c=0;c<e.length;c++){const u=e[c].claim_order,f=(s>0&&e[n[s]].claim_order<=u?s+1:$t(1,s,_=>e[n[_]].claim_order,u))-1;i[c]=n[f]+1;const a=f+1;n[a]=c,s=Math.max(a,s)}const l=[],r=[];let o=e.length-1;for(let c=n[s]+1;c!=0;c=i[c-1]){for(l.push(e[c-1]);o>=c;o--)r.push(e[o]);o--}for(;o>=0;o--)r.push(e[o]);l.reverse(),r.sort((c,u)=>c.claim_order-u.claim_order);for(let c=0,u=0;c<r.length;c++){for(;u<l.length&&r[c].claim_order>=l[u].claim_order;)u++;const f=u<l.length?l[u]:null;t.insertBefore(r[c],f)}}function vt(t,e){t.appendChild(e)}function st(t){if(!t)return document;const e=t.getRootNode?t.getRootNode():t.ownerDocument;return e&&e.host?e:t.ownerDocument}function Et(t){const e=I("style");return kt(st(t),e),e.sheet}function kt(t,e){vt(t.head||t,e)}function At(t,e){if(L){for(wt(t),(t.actual_end_child===void 0||t.actual_end_child!==null&&t.actual_end_child.parentElement!==t)&&(t.actual_end_child=t.firstChild);t.actual_end_child!==null&&t.actual_end_child.claim_order===void 0;)t.actual_end_child=t.actual_end_child.nextSibling;e!==t.actual_end_child?(e.claim_order!==void 0||e.parentNode!==t)&&t.insertBefore(e,t.actual_end_child):t.actual_end_child=e.nextSibling}else(e.parentNode!==t||e.nextSibling!==null)&&t.appendChild(e)}function Tt(t,e,n){t.insertBefore(e,n||null)}function Nt(t,e,n){L&&!n?At(t,e):(e.parentNode!==t||e.nextSibling!=n)&&t.insertBefore(e,n||null)}function C(t){t.parentNode.removeChild(t)}function Zt(t,e){for(let n=0;n<t.length;n+=1)t[n]&&t[n].d(e)}function I(t){return document.createElement(t)}function rt(t){return document.createElementNS("http://www.w3.org/2000/svg",t)}function W(t){return document.createTextNode(t)}function te(){return W(" ")}function ee(){return W("")}function ne(t,e,n,i){return t.addEventListener(e,n,i),()=>t.removeEventListener(e,n,i)}function St(t,e,n){n==null?t.removeAttribute(e):t.getAttribute(e)!==n&&t.setAttribute(e,n)}function ie(t,e){const n=Object.getOwnPropertyDescriptors(t.__proto__);for(const i in e)e[i]==null?t.removeAttribute(i):i==="style"?t.style.cssText=e[i]:i==="__value"?t.value=t[i]=e[i]:n[i]&&n[i].set?t[i]=e[i]:St(t,i,e[i])}function jt(t){return Array.from(t.childNodes)}function ct(t){t.claim_info===void 0&&(t.claim_info={last_index:0,total_claimed:0})}function lt(t,e,n,i,s=!1){ct(t);const l=(()=>{for(let r=t.claim_info.last_index;r<t.length;r++){const o=t[r];if(e(o)){const c=n(o);return c===void 0?t.splice(r,1):t[r]=c,s||(t.claim_info.last_index=r),o}}for(let r=t.claim_info.last_index-1;r>=0;r--){const o=t[r];if(e(o)){const c=n(o);return c===void 0?t.splice(r,1):t[r]=c,s?c===void 0&&t.claim_info.last_index--:t.claim_info.last_index=r,o}}return i()})();return l.claim_order=t.claim_info.total_claimed,t.claim_info.total_claimed+=1,l}function ot(t,e,n,i){return lt(t,s=>s.nodeName===e,s=>{const l=[];for(let r=0;r<s.attributes.length;r++){const o=s.attributes[r];n[o.name]||l.push(o.name)}l.forEach(r=>s.removeAttribute(r))},()=>i(e))}function se(t,e,n){return ot(t,e,n,I)}function re(t,e,n){return ot(t,e,n,rt)}function Ct(t,e){return lt(t,n=>n.nodeType===3,n=>{const i=""+e;if(n.data.startsWith(i)){if(n.data.length!==i.length)return n.splitText(i.length)}else n.data=i},()=>W(e),!0)}function ce(t){return Ct(t," ")}function Q(t,e,n){for(let i=n;i<t.length;i+=1){const s=t[i];if(s.nodeType===8&&s.textContent.trim()===e)return i}return t.length}function le(t,e){const n=Q(t,"HTML_TAG_START",0),i=Q(t,"HTML_TAG_END",n);if(n===i)return new U(void 0,e);ct(t);const s=t.splice(n,i-n+1);C(s[0]),C(s[s.length-1]);const l=s.slice(1,s.length-1);for(const r of l)r.claim_order=t.claim_info.total_claimed,t.claim_info.total_claimed+=1;return new U(l,e)}function oe(t,e){e=""+e,t.wholeText!==e&&(t.data=e)}function ue(t,e,n,i){n===null?t.style.removeProperty(e):t.style.setProperty(e,n,i?"important":"")}function ae(t,e,n){t.classList[n?"add":"remove"](e)}function ut(t,e,{bubbles:n=!1,cancelable:i=!1}={}){const s=document.createEvent("CustomEvent");return s.initCustomEvent(t,n,i,e),s}function fe(t,e=document.body){return Array.from(e.querySelectorAll(t))}class Mt{constructor(e=!1){this.is_svg=!1,this.is_svg=e,this.e=this.n=null}c(e){this.h(e)}m(e,n,i=null){this.e||(this.is_svg?this.e=rt(n.nodeName):this.e=I(n.nodeName),this.t=n,this.c(e)),this.i(i)}h(e){this.e.innerHTML=e,this.n=Array.from(this.e.childNodes)}i(e){for(let n=0;n<this.n.length;n+=1)Tt(this.t,this.n[n],e)}p(e){this.d(),this.h(e),this.i(this.a)}d(){this.n.forEach(C)}}class U extends Mt{constructor(e,n=!1){super(n),this.e=this.n=null,this.l=e}c(e){this.l?this.n=this.l:super.c(e)}i(e){for(let n=0;n<this.n.length;n+=1)Nt(this.t,this.n[n],e)}}const M=new Map;let D=0;function Dt(t){let e=5381,n=t.length;for(;n--;)e=(e<<5)-e^t.charCodeAt(n);return e>>>0}function Ht(t,e){const n={stylesheet:Et(e),rules:{}};return M.set(t,n),n}function at(t,e,n,i,s,l,r,o=0){const c=16.666/i;let u=`{
`;for(let m=0;m<=1;m+=c){const A=e+(n-e)*l(m);u+=m*100+`%{${r(A,1-A)}}
`}const f=u+`100% {${r(n,1-n)}}
}`,a=`__svelte_${Dt(f)}_${o}`,_=st(t),{stylesheet:d,rules:h}=M.get(_)||Ht(_,t);h[a]||(h[a]=!0,d.insertRule(`@keyframes ${a} ${f}`,d.cssRules.length));const p=t.style.animation||"";return t.style.animation=`${p?`${p}, `:""}${a} ${i}ms linear ${s}ms 1 both`,D+=1,a}function q(t,e){const n=(t.style.animation||"").split(", "),i=n.filter(e?l=>l.indexOf(e)<0:l=>l.indexOf("__svelte")===-1),s=n.length-i.length;s&&(t.style.animation=i.join(", "),D-=s,D||Lt())}function Lt(){G(()=>{D||(M.forEach(t=>{const{stylesheet:e}=t;let n=e.cssRules.length;for(;n--;)e.deleteRule(n);t.rules={}}),M.clear())})}let E;function v(t){E=t}function O(){if(!E)throw new Error("Function called outside component initialization");return E}function _e(t){O().$$.on_mount.push(t)}function de(t){O().$$.after_update.push(t)}function he(){const t=O();return(e,n,{cancelable:i=!1}={})=>{const s=t.$$.callbacks[e];if(s){const l=ut(e,n,{cancelable:i});return s.slice().forEach(r=>{r.call(t,l)}),!l.defaultPrevented}return!0}}function me(t,e){return O().$$.context.set(t,e),e}const w=[],V=[],S=[],B=[],ft=Promise.resolve();let z=!1;function _t(){z||(z=!0,ft.then(dt))}function pe(){return _t(),ft}function k(t){S.push(t)}function ye(t){B.push(t)}const R=new Set;let N=0;function dt(){const t=E;do{for(;N<w.length;){const e=w[N];N++,v(e),Ot(e.$$)}for(v(null),w.length=0,N=0;V.length;)V.pop()();for(let e=0;e<S.length;e+=1){const n=S[e];R.has(n)||(R.add(n),n())}S.length=0}while(w.length);for(;B.length;)B.pop()();z=!1,R.clear(),v(t)}function Ot(t){if(t.fragment!==null){t.update(),b(t.before_update);const e=t.dirty;t.dirty=[-1],t.fragment&&t.fragment.p(t.ctx,e),t.after_update.forEach(k)}}let $;function ht(){return $||($=Promise.resolve(),$.then(()=>{$=null})),$}function H(t,e,n){t.dispatchEvent(ut(`${e?"intro":"outro"}${n}`))}const j=new Set;let y;function ge(){y={r:0,c:[],p:y}}function xe(){y.r||b(y.c),y=y.p}function Pt(t,e){t&&t.i&&(j.delete(t),t.i(e))}function be(t,e,n,i){if(t&&t.o){if(j.has(t))return;j.add(t),y.c.push(()=>{j.delete(t),i&&(n&&t.d(1),i())}),t.o(e)}}const mt={duration:0};function $e(t,e,n){let i=e(t,n),s=!1,l,r,o=0;function c(){l&&q(t,l)}function u(){const{delay:a=0,duration:_=300,easing:d=X,tick:h=x,css:p}=i||mt;p&&(l=at(t,0,1,_,a,d,p,o++)),h(0,1);const m=et()+a,A=m+_;r&&r.abort(),s=!0,k(()=>H(t,!0,"start")),r=it(P=>{if(s){if(P>=A)return h(1,0),H(t,!0,"end"),c(),s=!1;if(P>=m){const J=d((P-m)/_);h(J,1-J)}}return s})}let f=!1;return{start(){f||(f=!0,q(t),F(i)?(i=i(),ht().then(u)):u())},invalidate(){f=!1},end(){s&&(c(),s=!1)}}}function we(t,e,n){let i=e(t,n),s=!0,l;const r=y;r.r+=1;function o(){const{delay:c=0,duration:u=300,easing:f=X,tick:a=x,css:_}=i||mt;_&&(l=at(t,1,0,u,c,f,_));const d=et()+c,h=d+u;k(()=>H(t,!1,"start")),it(p=>{if(s){if(p>=h)return a(0,1),H(t,!1,"end"),--r.r||b(r.c),!1;if(p>=d){const m=f((p-d)/u);a(1-m,m)}}return s})}return F(i)?ht().then(()=>{i=i(),o()}):o(),{end(c){c&&i.tick&&i.tick(1,0),s&&(l&&q(t,l),s=!1)}}}const ve=typeof window!="undefined"?window:typeof globalThis!="undefined"?globalThis:global;function Ee(t,e){const n={},i={},s={$$scope:1};let l=t.length;for(;l--;){const r=t[l],o=e[l];if(o){for(const c in r)c in o||(i[c]=1);for(const c in o)s[c]||(n[c]=o[c],s[c]=1);t[l]=o}else for(const c in r)s[c]=1}for(const r in i)r in n||(n[r]=void 0);return n}function ke(t){return typeof t=="object"&&t!==null?t:{}}function Ae(t,e,n){const i=t.$$.props[e];i!==void 0&&(t.$$.bound[i]=n,n(t.$$.ctx[i]))}function Te(t){t&&t.c()}function Ne(t,e){t&&t.l(e)}function Rt(t,e,n,i){const{fragment:s,on_mount:l,on_destroy:r,after_update:o}=t.$$;s&&s.m(e,n),i||k(()=>{const c=l.map(Y).filter(F);r?r.push(...c):b(c),t.$$.on_mount=[]}),o.forEach(k)}function qt(t,e){const n=t.$$;n.fragment!==null&&(b(n.on_destroy),n.fragment&&n.fragment.d(e),n.on_destroy=n.fragment=null,n.ctx=[])}function Bt(t,e){t.$$.dirty[0]===-1&&(w.push(t),_t(),t.$$.dirty.fill(0)),t.$$.dirty[e/31|0]|=1<<e%31}function Se(t,e,n,i,s,l,r,o=[-1]){const c=E;v(t);const u=t.$$={fragment:null,ctx:null,props:l,update:x,not_equal:s,bound:K(),on_mount:[],on_destroy:[],on_disconnect:[],before_update:[],after_update:[],context:new Map(e.context||(c?c.$$.context:[])),callbacks:K(),dirty:o,skip_bound:!1,root:e.target||c.$$.root};r&&r(u.root);let f=!1;if(u.ctx=n?n(t,e.props||{},(a,_,...d)=>{const h=d.length?d[0]:_;return u.ctx&&s(u.ctx[a],u.ctx[a]=h)&&(!u.skip_bound&&u.bound[a]&&u.bound[a](h),f&&Bt(t,a)),_}):[],u.update(),f=!0,b(u.before_update),u.fragment=i?i(u.ctx):!1,e.target){if(e.hydrate){xt();const a=jt(e.target);u.fragment&&u.fragment.l(a),a.forEach(C)}else u.fragment&&u.fragment.c();e.intro&&Pt(t.$$.fragment),Rt(t,e.target,e.anchor,e.customElement),bt(),dt()}v(c)}class je{$destroy(){qt(this,1),this.$destroy=x}$on(e,n){const i=this.$$.callbacks[e]||(this.$$.callbacks[e]=[]);return i.push(n),()=>{const s=i.indexOf(n);s!==-1&&i.splice(s,1)}}$set(e){this.$$set&&!yt(e)&&(this.$$.skip_bound=!0,this.$$set(e),this.$$.skip_bound=!1)}}export{ve as $,ke as A,qt as B,pt as C,pe as D,x as E,Ft as F,At as G,Gt as H,Zt as I,ne as J,k as K,$e as L,we as M,It as N,Jt as O,Kt as P,Wt as Q,Yt as R,je as S,rt as T,re as U,V,Ae as W,U as X,fe as Y,le as Z,ye as _,jt as a,ie as a0,ae as a1,Ut as a2,he as a3,Qt as a4,Vt as a5,Xt as a6,St as b,se as c,C as d,I as e,ue as f,Nt as g,Ct as h,Se as i,oe as j,te as k,ee as l,ce as m,ge as n,be as o,xe as p,Pt as q,me as r,zt as s,W as t,de as u,_e as v,Te as w,Ne as x,Rt as y,Ee as z};
