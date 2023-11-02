import{k as S,B as g,_ as M,l as i,m as P,n as f,w as m,j as n,x as t,A as r}from"./index-e628351f.js";import{S as L,a as q,b as _,V as l,c as x}from"./VSlider-2ab6e78e.js";import{V as C,a as V}from"./VRow-1e6bba2c.js";import"./tag-77e7f82a.js";const v=S({name:"IterativeMergeSort",components:{SortHeader:L,SDLCanvas:q,SortButton:_},setup(){return{store:g()}},data:()=>({sequenceLengthMappingParameter:0,comparisonsPerSecondMappingParameter:0,sequenceLengthMin:3,sequenceLengthMax:1e4,comparisonsPerSecondMin:1,comparisonsPerSecondMax:3e4,formatter:Intl.NumberFormat("en-US",{notation:"compact",compactDisplay:"short"})}),created(){this.setDefaults()},methods:{setDefaults(){this.store.setSortAlgorithm("iter_merge"),this.store.setSequenceLength(100),this.store.setComparisonsPerSecond(100),this.sequenceLengthMappingParameter=this.reverseExponentialMap(this.sequenceLengthMin,this.sequenceLengthMax,this.store.sequenceLength),this.comparisonsPerSecondMappingParameter=this.reverseExponentialMap(this.comparisonsPerSecondMin,this.comparisonsPerSecondMax,this.store.comparisonsPerSecond)},exponentialMap(e,o,s){return(Math.exp(Math.pow(s,3))-1)/(Math.E-1)*(o-e)+e},reverseExponentialMap(e,o,s){const a=Math.log(s/(o-e)+1)/Math.log(Math.E);return Math.pow(a,1/3)}},computed:{mappedSequenceLength:{get(){return this.sequenceLengthMappingParameter},set(e){this.sequenceLengthMappingParameter=e,this.store.setSequenceLength(Math.round(this.exponentialMap(this.sequenceLengthMin,this.sequenceLengthMax,e)))}},mappedComparisonsPerSecond:{get(){return this.comparisonsPerSecondMappingParameter},set(e){this.comparisonsPerSecondMappingParameter=e,this.store.setComparisonsPerSecond(Math.round(this.exponentialMap(this.comparisonsPerSecondMin,this.comparisonsPerSecondMax,e)))}}}}),w=t("h3",null,"Time complexity O(n log(n))",-1),y=t("h3",null,"Space complexity O(n)",-1),B=t("br",null,null,-1),D=t("br",null,null,-1),b=t("br",null,null,-1);function k(e,o,s,c,a,E){const u=i("SortHeader"),h=i("SDLCanvas"),d=i("SortButton");return P(),f(C,null,{default:m(()=>[n(u,{name:"Iterative Merge Sort",link:"https://www.geeksforgeeks.org/iterative-merge-sort/"}),w,y,B,t("p",null,r(e.formatter.format(e.store.comparisons))+" comparisons",1),n(h),t("p",null,"FPS: "+r(e.store.frameRate),1),D,n(V,{justify:"center"},{default:m(()=>[n(d)]),_:1}),b,n(x,null,{default:m(()=>[t("p",null,"Number of elements: "+r(e.formatter.format(e.store.sequenceLength)),1),n(l,{modelValue:e.mappedSequenceLength,"onUpdate:modelValue":o[0]||(o[0]=p=>e.mappedSequenceLength=p),min:"0",max:"1",color:"secondary"},null,8,["modelValue"]),t("p",null," Comparisons per second: "+r(e.formatter.format(e.store.comparisonsPerSecond)),1),n(l,{modelValue:e.mappedComparisonsPerSecond,"onUpdate:modelValue":o[1]||(o[1]=p=>e.mappedComparisonsPerSecond=p),min:"0",max:"1",color:"secondary"},null,8,["modelValue"])]),_:1})]),_:1})}const H=M(v,[["render",k]]);export{H as default};
