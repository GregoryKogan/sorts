import{k as S,B as g,_ as M,l as i,m as P,n as f,w as c,j as o,x as t,z as L,A as r}from"./index-32289a43.js";import{S as _,a as q,b as x,V as l,c as V}from"./VSlider-4792c6c0.js";import{V as C,a as w}from"./VRow-376413c0.js";import"./tag-ef337ca6.js";const b=S({name:"CountingSort",components:{SortHeader:_,SDLCanvas:q,SortButton:x},setup(){return{store:g()}},data:()=>({sequenceLengthMappingParameter:0,comparisonsPerSecondMappingParameter:0,sequenceLengthMin:3,sequenceLengthMax:1e4,comparisonsPerSecondMin:1,comparisonsPerSecondMax:3e4,formatter:Intl.NumberFormat("en-US",{notation:"compact",compactDisplay:"short"})}),created(){this.setDefaults()},methods:{setDefaults(){this.store.setSortAlgorithm("count"),this.store.setSequenceLength(100),this.store.setStepsPerSecond(50),this.sequenceLengthMappingParameter=this.reverseExponentialMap(this.sequenceLengthMin,this.sequenceLengthMax,this.store.sequenceLength),this.comparisonsPerSecondMappingParameter=this.reverseExponentialMap(this.comparisonsPerSecondMin,this.comparisonsPerSecondMax,this.store.stepsPerSecond)},exponentialMap(e,n,s){return(Math.exp(Math.pow(s,3))-1)/(Math.E-1)*(n-e)+e},reverseExponentialMap(e,n,s){const a=Math.log(s/(n-e)+1)/Math.log(Math.E);return Math.pow(a,1/3)}},computed:{mappedSequenceLength:{get(){return this.sequenceLengthMappingParameter},set(e){this.sequenceLengthMappingParameter=e,this.store.setSequenceLength(Math.round(this.exponentialMap(this.sequenceLengthMin,this.sequenceLengthMax,e)))}},mappedComparisonsPerSecond:{get(){return this.comparisonsPerSecondMappingParameter},set(e){this.comparisonsPerSecondMappingParameter=e,this.store.setStepsPerSecond(Math.round(this.exponentialMap(this.comparisonsPerSecondMin,this.comparisonsPerSecondMax,e)))}}}}),y=t("h3",null,"Time complexity O(n + m)",-1),B=t("h3",null,"Space complexity O(n + m)",-1),D=t("br",null,null,-1),k=t("br",null,null,-1),v=t("br",null,null,-1),E=t("br",null,null,-1);function N(e,n,s,m,a,$){const u=i("SortHeader"),h=i("SDLCanvas"),d=i("SortButton");return P(),f(C,null,{default:c(()=>[o(u,{name:"Counting Sort",link:"https://www.geeksforgeeks.org/counting-sort/"}),y,B,D,t("p",null,[L(r(e.formatter.format(e.store.comparisons))+" comparisons ",1),k]),o(h),t("p",null,"FPS: "+r(e.store.frameRate),1),v,o(w,{justify:"center"},{default:c(()=>[o(d)]),_:1}),E,o(V,null,{default:c(()=>[t("p",null,"Number of elements: "+r(e.formatter.format(e.store.sequenceLength)),1),o(l,{modelValue:e.mappedSequenceLength,"onUpdate:modelValue":n[0]||(n[0]=p=>e.mappedSequenceLength=p),min:"0",max:"1",color:"secondary"},null,8,["modelValue"]),t("p",null," Steps per second: "+r(e.formatter.format(e.store.stepsPerSecond)),1),o(l,{modelValue:e.mappedComparisonsPerSecond,"onUpdate:modelValue":n[1]||(n[1]=p=>e.mappedComparisonsPerSecond=p),min:"0",max:"1",color:"secondary"},null,8,["modelValue"])]),_:1})]),_:1})}const F=M(b,[["render",N]]);export{F as default};
