<template>
  <SortView
    name="Radix Sort"
    link="https://www.geeksforgeeks.org/radix-sort/"
    algorithm="radix"
    timeComplexity="O(d · (n + b))"
    spaceComplexity="O(n + b)"
    :showSwaps="false"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="5000"
    :defaultSequenceLength="1000"
    :defaultStepsPerSecond="500"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "RadixSort",
  components: { SortView },
});
</script>
