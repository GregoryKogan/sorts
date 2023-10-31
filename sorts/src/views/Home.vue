<template>
  <div class="canvas-wrapper"><SDLCanvas /></div>
  <v-container
    style="
      height: 100%;
      justify-content: end;
      align-items: end;
      display: flex;
      flex-direction: column;
    "
  >
    <v-card color="transparent" flat>FPS: {{ store.frameRate }}</v-card>
  </v-container>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SDLCanvas from "@/components/SDLCanvas.vue";
import { useAppStore } from "@/store/app";

export default defineComponent({
  name: "Home",
  components: {
    SDLCanvas,
  },
  setup() {
    const store = useAppStore();
    return { store };
  },
});
</script>

<style scoped>
.canvas-wrapper {
  width: 100vw;
  height: 100vh;
  position: absolute;
  top: 0;
  left: 0;
}
</style>
