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

      if ("frame_rate" in data.message) {
        this.store.setFrameRate(data.message.frame_rate);
      } else {
        console.log("Message: ", data.message);
      }
    });
  },
});
</script>

<style scoped>
* {
  margin: 0;
  padding: 0;
  overflow: hidden;
}
</style>
