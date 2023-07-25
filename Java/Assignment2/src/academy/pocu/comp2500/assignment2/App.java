package academy.pocu.comp2500.assignment2;

import academy.pocu.comp2500.assignment2.registry.Registry;

public class App {
    public App(Registry registry) {
        // register your classes or methods here
        registry.registerRedStampCreator("Stamp");
        registry.registerBlueStampCreator("Stamp");
        registry.registerGreenStampCreator("Stamp");

        registry.registerWallCalendarCreator("Calendar");
        registry.registerMagnetCalendarCreator("Calendar");
        registry.registerDeskCalendarCreator("Calendar");

        registry.registerLandscapeBannerCreator("Banner");
        registry.registerPortraitBannerCreator("Banner");
        registry.registerGlossBannerCreator("Banner");
        registry.registerScrimBannerCreator("Banner");
        registry.registerMeshBannerCreator("Banner");

        registry.registerLandscapeBusinessCardCreator("BusinessCard");
        registry.registerPortraitBusinessCardCreator("BusinessCard");

        registry.registerIvoryBusinessCardCreator("BusinessCard");
        registry.registerGrayBusinessCardCreator("BusinessCard");

        registry.registerWhiteBusinessCardCreator("BusinessCard");
        registry.registerLaidBusinessCardCreator("BusinessCard");

        registry.registerLinenBusinessCardCreator("BusinessCard");
        registry.registerSmoothBusinessCardCreator("BusinessCard");

        registry.registerSingleSidedBusinessCardCreator("BusinessCard");
        registry.registerDoubleSidedBusinessCardCreator("BusinessCard");

        registry.registerCartCreator("ShoppingCart");
        registry.registerProductAdder("ShoppingCart", "addProduct");
        registry.registerProductRemover("ShoppingCart", "removeProduct");
        registry.registerTotalPriceGetter("ShoppingCart", "getTotalPrice");

        registry.registerLandscapeBannerTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerLandscapeBannerImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerPortraitBannerTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerPortraitBannerImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerGlossBannerTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerGlossBannerImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerScrimBannerTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerScrimBannerImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerMeshBannerTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerMeshBannerImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerLandscapeBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerLandscapeBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerPortraitBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerPortraitBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerIvoryBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerIvoryBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerGrayBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerGrayBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerWhiteBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerWhiteBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerLaidBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerLaidBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerLinenBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerLinenBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerSmoothBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerSmoothBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerSingleSidedBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerSingleSidedBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");

        registry.registerDoubleSidedBusinessCardTextApertureAdder("CustomizableProduct", "addApertures");
        registry.registerDoubleSidedBusinessCardImageApertureAdder("CustomizableProduct", "addApertures");
    }
}
