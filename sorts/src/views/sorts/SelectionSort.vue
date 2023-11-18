<template>
  <SortView
    name="Selection Sort"
    link="https://www.geeksforgeeks.org/selection-sort/"
    algorithm="selection"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="2000"
    :maxStepsPerSecond="100000"
    :defaultSequenceLength="50"
    :defaultStepsPerSecond="50"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "SelectionSort",
  components: { SortView },
});
</script>
