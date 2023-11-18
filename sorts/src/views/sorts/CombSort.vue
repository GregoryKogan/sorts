<template>
  <SortView
    name="Comb Sort"
    link="https://www.geeksforgeeks.org/comb-sort/"
    algorithm="comb"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="20000"
    :defaultSequenceLength="500"
    :defaultStepsPerSecond="500"
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
