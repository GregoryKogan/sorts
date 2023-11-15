<template>
  <SortView
    name="Iterative Merge Sort"
    link="https://www.geeksforgeeks.org/iterative-merge-sort/"
    algorithm="iter_merge"
    timeComplexity="O(n log(n))"
    spaceComplexity="O(n)"
    :showSwaps="false"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="30000"
    :defaultSequenceLength="500"
    :defaultStepsPerSecond="250"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "IterativeMergeSort",
  components: { SortView },
});
</script>
