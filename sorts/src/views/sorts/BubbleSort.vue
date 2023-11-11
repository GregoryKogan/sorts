<template>
  <SortView
    name="Bubble Sort"
    link="https://www.geeksforgeeks.org/bubble-sort/"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="10000000"
    algorithm="bubble"
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
