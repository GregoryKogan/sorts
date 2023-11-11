<template>
  <SortView
    name="Gnome Sort"
    link="https://www.geeksforgeeks.org/gnome-sort-a-stupid-one/"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="10000"
    :maxStepsPerSecond="10000000"
    algorithm="gnome"
  />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SortView from "@/components/SortView.vue";

export default defineComponent({
  name: "GnomeSort",
  components: { SortView },
});
</script>
