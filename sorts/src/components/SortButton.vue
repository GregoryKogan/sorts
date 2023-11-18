<template>
  <v-btn @click="sort" variant="tonal" color="primary" size="large"
    >Sort!</v-btn
  >
</template>

<script lang="ts">
import { useAppStore } from "@/store/app";
import { defineComponent } from "vue";

export default defineComponent({
  name: "SortButton",
  setup() {
    const store = useAppStore();
    return { store };
  },
  methods: {
    sort() {
      window.postMessage(
        JSON.stringify({
          to: "cpp",
          message: {
            action: "sort",
            algorithm: this.store.sortAlgorithm,
            seq_len: this.store.sequenceLength,
            steps_per_sec: this.store.stepsPerSecond,
            reverse_input: this.store.reverseInput,
          },
        }),
        "*"
      );
    },
  },
});
</script>
