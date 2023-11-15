<template>
  <SortView
    name="Iterative Quick Sort"
    link="https://www.geeksforgeeks.org/iterative-quick-sort/"
    algorithm="iter_quick"
    timeComplexity="θ(n log(n))"
    spaceComplexity="O(n)"
    :showSwaps="true"
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
  name: "IterativeQuickSort",
  components: { SortView },
});
</script>
