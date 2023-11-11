<template>
  <SortView
    name="Quick Sort"
    link="https://www.geeksforgeeks.org/quick-sort/"
    timeComplexity="θ(n log(n))"
    spaceComplexity="O(n)"
    :showSwaps="true"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="30000"
    algorithm="quick"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "QuickSort",
  components: { SortView },
});
</script>
