import{k as i,_ as m,m as t,v as r,j as o,w as a,F as s,x as u,y as l,z as c,A as d}from"./index-20f07e2b.js";import{V as p,a as f,b as g}from"./VRow-894a4be1.js";import"./tag-7abb851e.js";const _=i({name:"Home",data:()=>({sorts:[{name:"bubble sort",route:"BubbleSort"},{name:"selection sort",route:"SelectionSort"},{name:"insertion sort",route:"InsertionSort"},{name:"merge sort",route:"MergeSort"},{name:"iterative merge sort",route:"IterativeMergeSort"}]}),mounted(){window.postMessage(JSON.stringify({to:"cpp",message:{action:"quit"}}),"*")}}),S=u("h1",{style:{"text-align":"center",margin:"1em"}},"Sorts",-1);function y(n,V,b,k,v,$){return t(),r(s,null,[S,o(p,null,{default:a(()=>[o(f,{justify:"space-around"},{default:a(()=>[(t(!0),r(s,null,l(n.sorts,e=>(t(),r("div",{key:e.name,style:{margin:"1em"}},[o(g,{onClick:h=>n.$router.push({name:e.route}),color:"primary",variant:"tonal"},{default:a(()=>[c(d(e.name),1)]),_:2},1032,["onClick"])]))),128))]),_:1})]),_:1})],64)}const C=m(_,[["render",y]]);export{C as default};
