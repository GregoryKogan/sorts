import{k as i,_ as m,m as t,v as o,j as r,w as a,F as s,x as l,y as u,z as c,A as d}from"./index-e628351f.js";import{V as p,a as f,b as _}from"./VRow-1e6bba2c.js";import"./tag-77e7f82a.js";const g=i({name:"Home",data:()=>({sorts:[{name:"bubble sort",route:"BubbleSort"},{name:"selection sort",route:"SelectionSort"},{name:"insertion sort",route:"InsertionSort"},{name:"iterative merge sort",route:"IterativeMergeSort"}]}),mounted(){window.postMessage(JSON.stringify({to:"cpp",message:{action:"quit"}}),"*")}}),y=l("h1",{style:{"text-align":"center",margin:"1em"}},"Sorts",-1);function S(n,V,b,k,v,$){return t(),o(s,null,[y,r(p,null,{default:a(()=>[r(f,{justify:"space-around"},{default:a(()=>[(t(!0),o(s,null,u(n.sorts,e=>(t(),o("div",{key:e.name,style:{margin:"1em"}},[r(_,{onClick:h=>n.$router.push({name:e.route}),color:"primary",variant:"tonal"},{default:a(()=>[c(d(e.name),1)]),_:2},1032,["onClick"])]))),128))]),_:1})]),_:1})],64)}const C=m(g,[["render",S]]);export{C as default};
