<template>
  <SortView
    name="Stooge Sort"
    link="https://www.geeksforgeeks.org/stooge-sort/"
    algorithm="stooge"
    timeComplexity="O(n³)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="250"
    :maxStepsPerSecond="500000"
    :defaultSequenceLength="50"
    :defaultStepsPerSecond="1000"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "StoogeSort",
  components: { SortView },
});
</script>
