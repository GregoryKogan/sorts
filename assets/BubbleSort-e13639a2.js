import{k as M,B as g,_ as f,l as i,m as P,n as L,w as m,j as s,x as t,z as c,A as n}from"./index-b61f649d.js";import{S as b,a as q,b as _,V as u,c as V}from"./VSlider-c31ff2a3.js";import{V as x,a as C}from"./VRow-54b544fe.js";import"./tag-8e7155a3.js";const B=M({name:"BubbleSort",components:{SortHeader:b,SDLCanvas:q,SortButton:_},setup(){return{store:g()}},data:()=>({sequenceLengthMappingParameter:0,comparisonsPerSecondMappingParameter:0,sequenceLengthMin:3,sequenceLengthMax:1e4,comparisonsPerSecondMin:1,comparisonsPerSecondMax:1e7,formatter:Intl.NumberFormat("en-US",{notation:"compact",compactDisplay:"short"})}),created(){this.setDefaults()},methods:{setDefaults(){this.store.setSortAlgorithm("bubble"),this.store.setSequenceLength(100),this.store.setComparisonsPerSecond(100),this.sequenceLengthMappingParameter=this.reverseExponentialMap(this.sequenceLengthMin,this.sequenceLengthMax,this.store.sequenceLength),this.comparisonsPerSecondMappingParameter=this.reverseExponentialMap(this.comparisonsPerSecondMin,this.comparisonsPerSecondMax,this.store.comparisonsPerSecond)},exponentialMap(e,o,r){return(Math.exp(Math.pow(r,3))-1)/(Math.E-1)*(o-e)+e},reverseExponentialMap(e,o,r){const a=Math.log(r/(o-e)+1)/Math.log(Math.E);return Math.pow(a,1/3)}},computed:{mappedSequenceLength:{get(){return this.sequenceLengthMappingParameter},set(e){this.sequenceLengthMappingParameter=e,this.store.setSequenceLength(Math.round(this.exponentialMap(this.sequenceLengthMin,this.sequenceLengthMax,e)))}},mappedComparisonsPerSecond:{get(){return this.comparisonsPerSecondMappingParameter},set(e){this.comparisonsPerSecondMappingParameter=e,this.store.setComparisonsPerSecond(Math.round(this.exponentialMap(this.comparisonsPerSecondMin,this.comparisonsPerSecondMax,e)))}}}}),w=t("h3",null,"Time complexity O(n²)",-1),y=t("h3",null,"Space complexity O(1)",-1),D=t("br",null,null,-1),k=t("br",null,null,-1),v=t("br",null,null,-1),E=t("br",null,null,-1);function N(e,o,r,l,a,$){const h=i("SortHeader"),d=i("SDLCanvas"),S=i("SortButton");return P(),L(x,null,{default:m(()=>[s(h,{name:"Bubble Sort",link:"https://www.geeksforgeeks.org/bubble-sort/"}),w,y,D,t("p",null,[c(n(e.formatter.format(e.store.comparisons))+" comparisons ",1),k,c(" "+n(e.formatter.format(e.store.swaps))+" swaps ",1)]),s(d),t("p",null,"FPS: "+n(e.store.frameRate),1),v,s(C,{justify:"center"},{default:m(()=>[s(S)]),_:1}),E,s(V,null,{default:m(()=>[t("p",null,"Number of elements: "+n(e.formatter.format(e.store.sequenceLength)),1),s(u,{modelValue:e.mappedSequenceLength,"onUpdate:modelValue":o[0]||(o[0]=p=>e.mappedSequenceLength=p),min:"0",max:"1",color:"secondary"},null,8,["modelValue"]),t("p",null," Comparisons per second: "+n(e.formatter.format(e.store.comparisonsPerSecond)),1),s(u,{modelValue:e.mappedComparisonsPerSecond,"onUpdate:modelValue":o[1]||(o[1]=p=>e.mappedComparisonsPerSecond=p),min:"0",max:"1",color:"secondary"},null,8,["modelValue"])]),_:1})]),_:1})}const F=f(B,[["render",N]]);export{F as default};