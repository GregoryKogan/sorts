<template>
  <SortView
    name="Iterative Quick Sort"
    link="https://www.geeksforgeeks.org/iterative-quick-sort/"
    timeComplexity="θ(n log(n))"
    spaceComplexity="O(n)"
    :showSwaps="true"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="30000"
    algorithm="iter_quick"
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
