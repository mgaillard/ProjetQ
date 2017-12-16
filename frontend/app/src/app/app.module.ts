import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule }   from '@angular/forms';
import { HttpModule }    from '@angular/http';

import { AppComponent } from './app.component';
import { SearchComponentComponent } from './search-component/search-component.component';
import { SearchResultListComponentComponent } from './search-result-list-component/search-result-list-component.component';

@NgModule({
  declarations: [
    AppComponent,
    SearchComponentComponent,
    SearchResultListComponentComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
