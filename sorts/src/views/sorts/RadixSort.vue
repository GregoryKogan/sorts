<template>
  <v-container>
    <SortHeader
      name="Radix Sort"
      link="https://www.geeksforgeeks.org/radix-sort/"
    />
    <h3>Time complexity O(d · (n + b))</h3>
    <h3>Space complexity O(n + b)</h3>
    <br />
    <p>
      {{ formatter.format(store.comparisons) }} comparisons <br />
      {{ formatter.format(store.swaps) }} swaps
    </p>
    <SDLCanvas />
    <p>FPS: {{ store.frameRate }}</p>
    <br />
    <v-row justify="center"><SortButton /></v-row>
    <br />
    <v-col>
      <p>Number of elements: {{ formatter.format(store.sequenceLength) }}</p>
      <v-slider
        v-model="mappedSequenceLength"
        min="0"
        max="1"
        color="secondary"
      ></v-slider>
      <p>
        Comparisons per second:
        {{ formatter.format(store.comparisonsPerSecond) }}
      </p>
      <v-slider
        v-model="mappedComparisonsPerSecond"
        min="0"
        max="1"
        color="secondary"
      ></v-slider>
    </v-col>
  </v-container>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { useAppStore } from "@/store/app";
import SortHeader from "@/components/SortHeader.vue";
import SDLCanvas from "@/components/SDLCanvas.vue";
import SortButton from "@/components/SortButton.vue";

export default defineComponent({
  name: "RadixSort",
  components: {
    SortHeader,
    SDLCanvas,
    SortButton,
  },
  setup() {
    const store = useAppStore();
    return { store };
  },
  data: () => ({
    sequenceLengthMappingParameter: 0,
    comparisonsPerSecondMappingParameter: 0,
    sequenceLengthMin: 3,
    sequenceLengthMax: 10000,
    comparisonsPerSecondMin: 1,
    comparisonsPerSecondMax: 30000,
    formatter: Intl.NumberFormat("en-US", {
      notation: "compact",
      compactDisplay: "short",
    }),
  }),
  created() {
    this.setDefaults();
  },
  methods: {
    setDefaults() {
      this.store.setSortAlgorithm("radix");
      this.store.setSequenceLength(100);
      this.store.setComparisonsPerSecond(50);

      this.sequenceLengthMappingParameter = this.reverseExponentialMap(
        this.sequenceLengthMin,
        this.sequenceLengthMax,
        this.store.sequenceLength
      );
      this.comparisonsPerSecondMappingParameter = this.reverseExponentialMap(
        this.comparisonsPerSecondMin,
        this.comparisonsPerSecondMax,
        this.store.comparisonsPerSecond
      );
    },
    exponentialMap(min: number, max: number, t: number) {
      const steepness = 3;
      const exp_t = (Math.exp(Math.pow(t, steepness)) - 1) / (Math.E - 1);
      return exp_t * (max - min) + min;
    },
    reverseExponentialMap(min: number, max: number, t: number) {
      const steepness = 3;
      const exp_t = Math.log(t / (max - min) + 1) / Math.log(Math.E);
      return Math.pow(exp_t, 1 / steepness);
    },
  },
  computed: {
    mappedSequenceLength: {
      get() {
        return this.sequenceLengthMappingParameter;
      },
      set(value: number) {
        this.sequenceLengthMappingParameter = value;
        this.store.setSequenceLength(
          Math.round(
            this.exponentialMap(
              this.sequenceLengthMin,
              this.sequenceLengthMax,
              value
            )
          )
        );
      },
    },
    mappedComparisonsPerSecond: {
      get() {
        return this.comparisonsPerSecondMappingParameter;
      },
      set(value: number) {
        this.comparisonsPerSecondMappingParameter = value;
        this.store.setComparisonsPerSecond(
          Math.round(
            this.exponentialMap(
              this.comparisonsPerSecondMin,
              this.comparisonsPerSecondMax,
              value
            )
          )
        );
      },
    },
  },
});
</script>
