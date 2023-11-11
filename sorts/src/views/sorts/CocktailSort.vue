<template>
  <SortView
    name="Cocktail Sort"
    link="https://www.geeksforgeeks.org/cocktail-sort/"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="10000000"
    algorithm="cocktail"
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
