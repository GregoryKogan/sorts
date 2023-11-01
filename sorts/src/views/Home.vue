<template>
  <h1 style="text-align: center; margin: 1em">Sorts</h1>

  <v-container>
    <v-row justify="space-around">
      <div v-for="sort in sorts" :key="sort.name" style="margin: 1em">
        <v-btn
          @click="$router.push({ name: sort.route })"
          color="primary"
          variant="tonal"
          >{{ sort.name }}</v-btn
        >
      </div>
    </v-row>
  </v-container>
</template>

<script lang="ts">
import { defineComponent } from "vue";

interface Sort {
  name: string;
  route: string;
}

export default defineComponent({
  name: "Home",
  data: () => ({
    sorts: [
      { name: "bubble sort", route: "BubbleSort" },
      { name: "selection sort", route: "SelectionSort" },
    ] as Sort[],
  }),
  mounted() {
    window.postMessage(
      JSON.stringify({
        to: "cpp",
        message: {
          action: "quit",
        },
      }),
      "*"
    );
  },
});
</script>
