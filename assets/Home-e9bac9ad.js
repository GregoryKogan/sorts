import{k as i,_ as m,m as t,v as o,j as r,w as a,F as s,x as u,y as c,z as l,A as d}from"./index-7552f18f.js";import{V as S,a as p,b as g}from"./VRow-ea3e0bd7.js";import"./tag-10603db1.js";const f=i({name:"Home",data:()=>({sorts:[{name:"bubble sort",route:"BubbleSort"},{name:"selection sort",route:"SelectionSort"},{name:"insertion sort",route:"InsertionSort"},{name:"merge sort",route:"MergeSort"},{name:"iterative merge sort",route:"IterativeMergeSort"},{name:"quick sort",route:"QuickSort"},{name:"iterative quick sort",route:"IterativeQuickSort"},{name:"heap sort",route:"HeapSort"},{name:"counting sort",route:"CountingSort"},{name:"cocktail sort",route:"CocktailSort"},{name:"radix sort",route:"RadixSort"},{name:"shell sort",route:"ShellSort"},{name:"gnome sort",route:"GnomeSort"},{name:"odd-even sort",route:"OddEvenSort"},{name:"comb sort",route:"CombSort"},{name:"cycle sort",route:"CycleSort"},{name:"bogo sort",route:"BogoSort"},{name:"stooge sort",route:"StoogeSort"}]}),mounted(){window.postMessage(JSON.stringify({to:"cpp",message:{action:"quit"}}),"*")}}),k=u("h1",{style:{"text-align":"center",margin:"1em"}},"Sorts",-1);function _(n,v,y,b,C,h){return t(),o(s,null,[k,r(S,null,{default:a(()=>[r(p,{justify:"space-around"},{default:a(()=>[(t(!0),o(s,null,c(n.sorts,e=>(t(),o("div",{key:e.name,style:{margin:"1em"}},[r(g,{onClick:x=>n.$router.push({name:e.route}),color:"primary",variant:"tonal"},{default:a(()=>[l(d(e.name),1)]),_:2},1032,["onClick"])]))),128))]),_:1})]),_:1})],64)}const w=m(f,[["render",_]]);export{w as default};