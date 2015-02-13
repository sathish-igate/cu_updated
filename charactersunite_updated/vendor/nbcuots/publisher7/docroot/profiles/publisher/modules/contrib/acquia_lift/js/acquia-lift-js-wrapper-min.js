(function(){var e,t=function(e,t){return function(){return e.apply(t,arguments)}},n=[].slice;window.AcquiaLiftJS=function(){function a(n,r,i){var s,o,u,a,f,l,c,h,p;this.owner=n,this.apikey=r,this.opts=i!=null?i:{},this.send=t(this.send,this),this.goal=t(this.goal,this),this.decision=t(this.decision,this),(s=this.opts).server==null&&(s.server="//api.lift.acquia.com"),(o=this.opts).timeout==null&&(o.timeout=5e3),(u=this.opts).cookies==null&&(u.cookies={ttl:2592e3,path:"/"}),(a=this.opts).scodestore==null&&(a.scodestore=CookieLite),(f=this.opts).session==null&&(f.session=typeof (l=this.opts).scodestore=="function"?l.scodestore("mpid"):void 0),(c=this.opts).transport==null&&(c.transport=e),(h=this.opts).batching==null&&(h.batching="off"),((p=this.opts.batching)==="auto"||p==="manual")&&this.batchStart()}var r,i,s,o,u;return a.prototype.decision=function(e,t,n){var r,s,o,u,a;t==null&&(t={}),n==null&&(n=null),o=[e,"decisions"],r=null;if(t.choices!=null){a=t.choices;for(s in a){u=a[s];if((u!=null?u.join:void 0)==null)continue;o.push(""+s+":"+u.join(",")),r==null&&(r={}),r[s]||(r[s]={code:u[0]})}delete t.choices}return t.fallback!=null&&(r=t.fallback,delete t.fallback),this.send(o,t,null,!0,function(e){return function(t){var s,o;i(e.opts,t!=null?t.session:void 0);if(n==null)return;return s=(o=t!=null?t.decisions:void 0)!=null?o:r,n(s,t!=null?t.session:void 0)}}(this))},a.prototype.goal=function(e,t,n){var r;return r=[e,"goal"],t.goal!=null&&(r.push(t.goal),delete t.goal),this.send(r,t,null,!0,function(e){return function(t){var r,s;i(e.opts,t!=null?t.session:void 0);if(n==null)return;return r=(t!=null?t.reward:void 0)>0,s=(t!=null?t.agent:void 0)==null,n(r,t!=null?t.session:void 0,s)}}(this))},a.prototype.send=function(e,t,n,r,i){var a;t.apikey=this.apikey,this.opts.session!=null&&(t.session=this.opts.session),t._t=(new Date).getTime();if(!r||(a=this.opts.batching)!=="auto"&&a!=="manual")return e=""+this.opts.server+"/"+this.owner+"/"+e.join("/")+"?"+s(t),new this.opts.transport(e,n,this.opts.timeout,function(e){return function(e){var t,n;try{return n=JSON.parse(e),i(n)}catch(r){return t=r,i(null)}}}(this));this.batch.push(o(e,t,i)),this.opts.batching==="auto"&&u(this);return},s=function(e){var t,n,r;n="";for(t in e)r=e[t],n+="&"+t+"="+escape(r);return n},i=function(e,t){if(t!=null&&e.cookies!=null)return e.session=t,typeof e.scodestore=="function"?e.scodestore("mpid",t,e.cookies):void 0},r=function(e,t){var r;return r=null,function(){var i;return i=1<=arguments.length?n.call(arguments,0):[],clearTimeout(r),setTimeout(function(e){return function(){return t.apply(e,i)}}(this),e)}},a.prototype.batchStart=function(){return this.batch=[]},a.prototype.batchSend=function(){var e,t;t=["-","batch"],e=this.batch.concat(),this.batchStart();if(e.length>0)return this.send(t,{},e,!1,function(t){var n,r,i;i=[];for(n in e)r=t!=null?t[n]:void 0,i.push(e[n].cb(r!=null?r.data:void 0));return i});return},u=r(20,function(e){return e.batchSend()}),o=function(e,t,n){var r;r={agent:e[0],type:e[1],query:t,cb:n};switch(r.type){case"decisions":e.length>2&&(r.choices=e.slice(2).join("/"));break;case"goal":e.length>2&&(r.goal=e[2])}return r},a}(),e=function(){function t(t,n,r,i){var s;s=e(t,n);if(s==null)return i(null);typeof r=="number"&&(s.timeout=r),s.onload=function(){return i(s.responseText)},s.onerror=s.ontimeout=function(){return i(null)},n!=null?(s.setRequestHeader("Content-Type","application/json"),s.send(JSON.stringify(n))):s.send()}var e;return e=function(e,t){var n,r;return n=t!=null?"POST":"GET",typeof XMLHttpRequest!="undefined"&&XMLHttpRequest!==null&&(r=new XMLHttpRequest),(r!=null?r.withCredentials:void 0)!=null?r.open(n,e,!0):typeof XDomainRequest!="undefined"&&XDomainRequest!==null?(r=new XDomainRequest,r.open(n,e)):r=null,r},t}()}).call(this);