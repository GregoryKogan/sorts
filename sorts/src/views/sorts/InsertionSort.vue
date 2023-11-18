<template>
  <SortView
    name="Insertion Sort"
    link="https://www.geeksforgeeks.org/insertion-sort/"
    algorithm="insertion"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="2000"
    :maxStepsPerSecond="100000"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "InsertionSort",
  components: { SortView },
});
</script>
