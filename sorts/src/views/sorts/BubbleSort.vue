<template>
  <v-container>
    <SortHeader
      name="Bubble Sort"
      link="https://www.geeksforgeeks.org/bubble-sort/"
    />
    <h3>Time complexity O(n²)</h3>
    <h3>Space complexity O(1)</h3>
    <br />
    <p>
      comparisons: {{ store.comparisons }} <br />
      swaps: {{ store.swaps }}
    </p>
    <SDLCanvas />
    <p>FPS: {{ store.frameRate }}</p>
    <br />
    <v-row justify="center">
      <SortButton />
    </v-row>
  </v-container>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { useAppStore } from "@/store/app";
import SortHeader from "@/components/SortHeader.vue";
import SDLCanvas from "@/components/SDLCanvas.vue";
import SortButton from "@/components/SortButton.vue";

export default defineComponent({
  name: "BubbleSort",
  components: {
    SortHeader,
    SDLCanvas,
    SortButton,
  },
  setup() {
    const store = useAppStore();
    return { store };
  },
});
</script>
