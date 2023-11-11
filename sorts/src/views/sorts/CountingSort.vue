<template>
  <SortView
    name="Counting Sort"
    link="https://www.geeksforgeeks.org/counting-sort/"
    timeComplexity="O(n + m)"
    spaceComplexity="O(n + m)"
    :showSwaps="false"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="30000"
    algorithm="count"
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
