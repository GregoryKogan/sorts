<template>
  <SortView
    name="Shell Sort"
    link="https://www.geeksforgeeks.org/shellsort/"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="false"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="30000"
    algorithm="shell"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "ShellSort",
  components: { SortView },
});
</script>
