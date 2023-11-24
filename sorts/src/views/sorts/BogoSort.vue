<template>
  <SortView
    name="Bogo Sort"
    link="https://www.geeksforgeeks.org/bogosort-permutation-sort/"
    algorithm="bogo"
    timeComplexity="θ(n * n!)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="10"
    :maxStepsPerSecond="1000000"
    :defaultSequenceLength="5"
    :defaultStepsPerSecond="100"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "BogoSort",
  components: { SortView },
});
</script>
