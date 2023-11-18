<template>
  <SortView
    name="Cycle Sort"
    link="https://www.geeksforgeeks.org/cycle-sort/"
    algorithm="cycle"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="1000"
    :maxStepsPerSecond="100000"
    :defaultSequenceLength="50"
    :defaultStepsPerSecond="50"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "CycleSort",
  components: { SortView },
});
</script>
