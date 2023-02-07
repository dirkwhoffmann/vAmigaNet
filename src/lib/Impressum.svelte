<script lang="ts">
	import MyButton from '$lib/widgets/MyButton.svelte';
	import { fade } from 'svelte/transition';
	import { showImpressum } from '$lib/stores';

	function close() {
        console.log("close");
		$showImpressum = false;
	}
</script>

<div
	class="absolute top-0 left-0 h-screen w-screen flex justify-center items-center"
	transition:fade
>
	<div class="relative w-2/3 h-2/3 flex flex-col py-4 justify-center bg-gray-700 text-gray-300 border-2 border-gray-300 rounded-xl font-josefin">
		<!-- Header -->
		<div class="w-full text-center text-3xl font-semibold text-white">Impressum</div>
        <hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />

		<!-- Main -->
		<div class="grow overflow-scroll px-4 border-blue-500">
			<div>
				<div class="text-3xl font-semibold pb-4 text-white">Kontakt</div>
				<div>
					<div>Prof. Dr. Dirk W. Hoffmann</div>
					<div>Hochschule Karlsruhe</div>
					<div>Moltkestraße 30</div>
					<div>D - 76133 Karlsruhe</div>
					<div>Germany</div>
				</div>
				<div class="text-3xl font-semibold py-4 text-white">Datenschutz</div>
				<p>
					Durch die Nutzung unserer Website erklären Sie sich mit der Erhebung, Verarbeitung und
					Nutzung von Daten gemäß der nachfolgenden Beschreibung einverstanden. Unsere Website kann
					grundsätzlich ohne Registrierung besucht werden. Dabei werden Daten wie beispielsweise
					aufgerufene Seiten bzw. Namen der abgerufenen Datei, Datum und Uhrzeit zu statistischen
					Zwecken auf dem Server gespeichert, ohne dass diese Daten unmittelbar auf Ihre Person
					bezogen werden. Personenbezogene Daten, insbesondere Name, Adresse oder E-Mail-Adresse
					werden soweit möglich auf freiwilliger Basis erhoben. Ohne Ihre Einwilligung erfolgt keine
					Weitergabe der Daten an Dritte.
				</p>
				<div class="text-3xl font-semibold py-4 text-white">Hosting</div>
				<p>
					Diese Webseite wird gehostet auf Servern der Github Inc., 88 Colin P Kelly Jr. Street, San
					Francisco, CA 94107, USA. GitHub kann beim Aufruf dieser Webseiten technische
					Informationen inklusive ihrer IP Adresse aufzeichnen. Weitere Informationen zum Umgang mit
					Nutzerdaten finden Sie in der
					<a href="https://help.github.com/articles/github-privacy-policy" class="text-white"
						>Datenschutzerklärung von GitHub</a
					>.
				</p>
			</div>
		</div>

		<!-- Footer -->
        <hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />
		<div class="w-full flex justify-center">
			<MyButton on:click={close} label="Close" />
		</div>
	</div>
</div>
