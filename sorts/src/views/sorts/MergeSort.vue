<template>
  <SortView
    name="Merge Sort"
    link="https://www.geeksforgeeks.org/merge-sort/"
    timeComplexity="O(n log(n))"
    spaceComplexity="O(n)"
    :showSwaps="false"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="30000"
    algorithm="merge"
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
