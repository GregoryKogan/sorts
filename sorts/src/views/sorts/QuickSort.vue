<template>
  <SortView
    name="Quick Sort"
    link="https://www.geeksforgeeks.org/quick-sort/"
    algorithm="quick"
    timeComplexity="θ(n log(n))"
    spaceComplexity="O(n)"
    :showSwaps="true"
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
  name: "QuickSort",
  components: { SortView },
});
</script>
