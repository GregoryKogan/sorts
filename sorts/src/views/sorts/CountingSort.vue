<template>
  <SortView
    name="Counting Sort"
    link="https://www.geeksforgeeks.org/counting-sort/"
    algorithm="count"
    timeComplexity="O(n + m)"
    spaceComplexity="O(n + m)"
    :showSwaps="false"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="5000"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "CountingSort",
  components: { SortView },
});
</script>
