<template>
  <SortView
    name="Selection Sort"
    link="https://www.geeksforgeeks.org/selection-sort/"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="10000000"
    algorithm="selection"
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
