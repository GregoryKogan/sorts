import{k as i,_ as u,m as t,v as o,j as r,w as a,F as s,x as m,y as c,z as l,A as p}from"./index-98b3825a.js";import{V as d,a as g,b as S}from"./VRow-ef6e4055.js";import"./tag-6dcf017e.js";const f=i({name:"Home",data:()=>({sorts:[{name:"bubble sort",route:"BubbleSort"},{name:"selection sort",route:"SelectionSort"},{name:"insertion sort",route:"InsertionSort"},{name:"merge sort",route:"MergeSort"},{name:"iterative merge sort",route:"IterativeMergeSort"},{name:"quick sort",route:"QuickSort"},{name:"iterative quick sort",route:"IterativeQuickSort"},{name:"heap sort",route:"HeapSort"},{name:"counting sort",route:"CountingSort"},{name:"cocktail sort",route:"CocktailSort"}]}),mounted(){window.postMessage(JSON.stringify({to:"cpp",message:{action:"quit"}}),"*")}}),k=m("h1",{style:{"text-align":"center",margin:"1em"}},"Sorts",-1);function _(n,v,y,C,V,b){return t(),o(s,null,[k,r(d,null,{default:a(()=>[r(g,{justify:"space-around"},{default:a(()=>[(t(!0),o(s,null,c(n.sorts,e=>(t(),o("div",{key:e.name,style:{margin:"1em"}},[r(S,{onClick:h=>n.$router.push({name:e.route}),color:"primary",variant:"tonal"},{default:a(()=>[l(p(e.name),1)]),_:2},1032,["onClick"])]))),128))]),_:1})]),_:1})],64)}const B=u(f,[["render",_]]);export{B as default};
