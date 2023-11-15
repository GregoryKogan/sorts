<template>
  <SortView
    name="Bubble Sort"
    link="https://www.geeksforgeeks.org/bubble-sort/"
    algorithm="bubble"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="1000"
    :maxStepsPerSecond="50000"
    :defaultSequenceLength="50"
    :defaultStepsPerSecond="50"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "BubbleSort",
  components: { SortView },
});
</script>
