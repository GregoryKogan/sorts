<template>
  <SortView
    name="Gnome Sort"
    link="https://www.geeksforgeeks.org/gnome-sort-a-stupid-one/"
    algorithm="gnome"
    timeComplexity="O(n²)"
    spaceComplexity="O(1)"
    :showSwaps="true"
    :maxSequenceLength="5000"
    :maxStepsPerSecond="500000"
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
