import{k as M,B as g,_ as P,l as i,m as _,n as L,w as l,j as t,x as n,z as m,A as o}from"./index-11971e17.js";import{S as f,a as x,b as q,V as u,c as V}from"./VSlider-a6a45b3d.js";import{V as C,a as w}from"./VRow-f5d15f86.js";import"./tag-549c7023.js";const B=M({name:"SelectionSort",components:{SortHeader:f,SDLCanvas:x,SortButton:q},setup(){return{store:g()}},data:()=>({sequenceLengthMappingParameter:0,comparisonsPerSecondMappingParameter:0,sequenceLengthMin:3,sequenceLengthMax:1e4,comparisonsPerSecondMin:1,comparisonsPerSecondMax:1e7}),created(){this.setDefaults()},methods:{setDefaults(){this.store.setSortAlgorithm("selection"),this.store.setSequenceLength(100),this.store.setComparisonsPerSecond(100),this.sequenceLengthMappingParameter=this.reverseExponentialMap(this.sequenceLengthMin,this.sequenceLengthMax,this.store.sequenceLength),this.comparisonsPerSecondMappingParameter=this.reverseExponentialMap(this.comparisonsPerSecondMin,this.comparisonsPerSecondMax,this.store.comparisonsPerSecond)},exponentialMap(e,s,r){return(Math.exp(Math.pow(r,3))-1)/(Math.E-1)*(s-e)+e},reverseExponentialMap(e,s,r){const a=Math.log(r/(s-e)+1)/Math.log(Math.E);return Math.pow(a,1/3)}},computed:{mappedSequenceLength:{get(){return this.sequenceLengthMappingParameter},set(e){this.sequenceLengthMappingParameter=e,this.store.setSequenceLength(Math.round(this.exponentialMap(this.sequenceLengthMin,this.sequenceLengthMax,e)))}},mappedComparisonsPerSecond:{get(){return this.comparisonsPerSecondMappingParameter},set(e){this.comparisonsPerSecondMappingParameter=e,this.store.setComparisonsPerSecond(Math.round(this.exponentialMap(this.comparisonsPerSecondMin,this.comparisonsPerSecondMax,e)))}}}}),b=n("h3",null,"Time complexity O(n²)",-1),k=n("h3",null,"Space complexity O(1)",-1),y=n("br",null,null,-1),D=n("br",null,null,-1),v=n("br",null,null,-1),E=n("br",null,null,-1),N=n("br",null,null,-1);function $(e,s,r,c,a,A){const d=i("SortHeader"),h=i("SDLCanvas"),S=i("SortButton");return _(),L(C,null,{default:l(()=>[t(d,{name:"Selection Sort",link:"https://www.geeksforgeeks.org/selection-sort/"}),b,k,y,n("p",null,[m(" comparisons: "+o(e.store.comparisons)+" ",1),D,m(" swaps: "+o(e.store.swaps)+" ",1),v]),t(h),n("p",null,"FPS: "+o(e.store.frameRate),1),E,t(w,{justify:"center"},{default:l(()=>[t(S)]),_:1}),N,t(V,null,{default:l(()=>[n("p",null,"Number of elements: "+o(e.store.sequenceLength),1),t(u,{modelValue:e.mappedSequenceLength,"onUpdate:modelValue":s[0]||(s[0]=p=>e.mappedSequenceLength=p),min:"0",max:"1",color:"secondary"},null,8,["modelValue"]),n("p",null,"Comparisons per second: "+o(e.store.comparisonsPerSecond),1),t(u,{modelValue:e.mappedComparisonsPerSecond,"onUpdate:modelValue":s[1]||(s[1]=p=>e.mappedComparisonsPerSecond=p),min:"0",max:"1",color:"secondary"},null,8,["modelValue"])]),_:1})]),_:1})}const T=P(B,[["render",$]]);export{T as default};