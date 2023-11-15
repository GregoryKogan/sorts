<template>
  <SortView
    name="Cocktail Sort"
    link="https://www.geeksforgeeks.org/cocktail-sort/"
    algorithm="cocktail"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="5000"
    :maxStepsPerSecond="500000"
    :defaultSequenceLength="50"
    :defaultStepsPerSecond="50"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "CocktailSort",
  components: { SortView },
});
</script>
