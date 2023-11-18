<template>
  <router-view />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { useAppStore } from "@/store/app";

export default defineComponent({
  name: "App",
  setup() {
    const store = useAppStore();
    return { store };
  },
  created() {
    window.addEventListener("message", (event) => {
      let data;

      try {
        data = JSON.parse(event.data);
        data = JSON.parse(data);
      } catch (e) {
        return;
      }

      if (!data.to || data.to !== "js") return;
      if (!data.message) return;

      if ("app_is_ready" in data.message) {
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
      }
      if ("frame_rate" in data.message)
        this.store.setFrameRate(data.message.frame_rate);
      if ("comparisons" in data.message)
        this.store.setComparisons(data.message.comparisons);
      if ("swaps" in data.message) this.store.setSwaps(data.message.swaps);
    });
  },
});
</script>

<style>
body {
  background-color: rgb(var(--v-theme-background));
}
</style>
