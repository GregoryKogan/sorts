<template>
  <SortView
    name="Comb Sort"
    link="https://www.geeksforgeeks.org/comb-sort/"
    algorithm="comb"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="5000"
    :maxStepsPerSecond="10000"
    :defaultSequenceLength="50"
    :defaultStepsPerSecond="50"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "CombSort",
  components: { SortView },
});
</script>
