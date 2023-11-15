<template>
  <SortView
    name="Odd-Even Sort"
    link="https://www.geeksforgeeks.org/odd-even-sort-brick-sort/"
    algorithm="odd-even"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="1000"
    :maxStepsPerSecond="50000"
    :defaultSequenceLength="250"
    :defaultStepsPerSecond="1000"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "OddEvenSort",
  components: { SortView },
});
</script>
