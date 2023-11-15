<template>
  <SortView
    name="Heap Sort"
    link="https://www.geeksforgeeks.org/heap-sort/"
    algorithm="heap"
    timeComplexity="O(n log(n))"
    spaceComplexity="O(n)"
    :showSwaps="true"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="30000"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "HeapSort",
  components: { SortView },
});
</script>
