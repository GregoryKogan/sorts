<template>
  <SortView
    name="Merge Sort"
    link="https://www.geeksforgeeks.org/merge-sort/"
    algorithm="merge"
    timeComplexity="O(n log(n))"
    spaceComplexity="O(n)"
    :showSwaps="false"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="10000"
    :defaultSequenceLength="500"
    :defaultStepsPerSecond="250"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "MergeSort",
  components: { SortView },
});
</script>
